#pragma once

#include <Windows.h>
#include <synchapi.h>
#include <thread>
#include <ntstatus.h>
#include <time.h>
#include <random>

#include "Requests.hpp"

#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)

typedef struct _CALL_DATA
{
	PVOID Function;
	ULONG_PTR Param;
} CALL_DATA, * PCALL_DATA;

void CallFunction(PCALL_DATA CallData)
{
	using tFn = NTSTATUS(__stdcall*)(UINT_PTR Param1);
	const auto fn = static_cast<tFn>(CallData->Function);

	fn(CallData->Param);
}

class KernelInterface
{
private:

	REQUEST_PACKET RequestPacket;
	HANDLE KernelEvent;
	HANDLE UserEvent;

public:

	HANDLE TargetProcessId;

	NTSTATUS Setup()
	{
		auto User32Module = LoadLibraryA("user32.dll");

		if (User32Module == NULL)
		{
			return STATUS_NOT_FOUND;
		}


		auto Win32uModule = LoadLibraryA("win32u.dll");

		if (Win32uModule == NULL)
		{
			return STATUS_NOT_FOUND;
		}


		PVOID ExportedFunction = GetProcAddress(Win32uModule, "NtTokenManagerCreateFlipObjectReturnTokenHandle");

		if (ExportedFunction == NULL)
		{
			return STATUS_NOT_FOUND;
		}


		WCHAR Characters[63] = L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

		WCHAR UserEventName[0xFF] = L"\\BaseNamedObjects\\Global\\";
		WCHAR KernelEventName[0xFF] = L"\\BaseNamedObjects\\Global\\";

		srand(time(NULL));
		int NameLength = rand() % 8 + 10;


		for (SIZE_T I = 0; I <= NameLength; I++)
		{
			UserEventName[I + 25] = Characters[rand() % 62];
		}

		for (SIZE_T I = 0; I <= NameLength; I++)
		{
			KernelEventName[I + 25] = Characters[rand() % 62];
		}

		this->UserEvent = CreateEventW(NULL, FALSE, FALSE, &UserEventName[18]);
		this->KernelEvent = CreateEventW(NULL, FALSE, FALSE, &KernelEventName[18]);

		if (this->UserEvent == NULL || this->KernelEvent == NULL)
		{
			return STATUS_UNSUCCESSFUL;
		}

		INIT_PACKET InitPacket = { };

		InitPacket.RequestBuffer = &this->RequestPacket;
		InitPacket.UserProcessId = (HANDLE)GetCurrentProcessId();
		RtlCopyMemory(InitPacket.KernelEventName, KernelEventName, sizeof(KernelEventName));
		RtlCopyMemory(InitPacket.UserEventName, UserEventName, sizeof(UserEventName));


		printf("InitPacket->KernelEventName : %S\n", InitPacket.KernelEventName);
		printf("InitPacket->UserEventName : %S\n", InitPacket.UserEventName);

		CALL_DATA CallData = { };

		CallData.Function = ExportedFunction;
		CallData.Param = (ULONG_PTR)&InitPacket;

		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)CallFunction, &CallData, 0, 0);
		WaitForSingleObject(this->KernelEvent, 1000 * 60); // 3 minutes

		return InitPacket.IsInitialized ? STATUS_SUCCESS : STATUS_UNSUCCESSFUL;
	}

	NTSTATUS Unload()
	{
		RtlZeroMemory(&this->RequestPacket, sizeof(this->RequestPacket));

		this->RequestPacket.Type = RequestType::Unload;
		this->RequestPacket.Status = STATUS_PENDING;

		SetEvent(this->UserEvent);
		WaitForSingleObject(this->KernelEvent,  1000 * 60); // 3 minutes

		return this->RequestPacket.Status;
	}

	void SetTargetProcessId(HANDLE ProcessId)
	{
		this->TargetProcessId = ProcessId;
	}

	UINT_PTR GetMainModule()
	{
		RtlZeroMemory(&this->RequestPacket, sizeof(this->RequestPacket));

		MAIN_MODULE_PACKET MainModulePacket = { };

		MainModulePacket.ProcessId = this->TargetProcessId;

		this->RequestPacket.Type = RequestType::MainModule;
		this->RequestPacket.Buffer = &MainModulePacket;
		this->RequestPacket.Status = STATUS_PENDING;

		SetEvent(this->UserEvent);
		WaitForSingleObject(this->KernelEvent,  1000 * 60); // 3 minutes

		if (!NT_SUCCESS(this->RequestPacket.Status))
		{
			return NULL;
		}

		return (UINT_PTR)MainModulePacket.Result;
	}

	NTSTATUS Read(PVOID SourceAddress, PVOID TargetAddress, SIZE_T Size)
	{
		RtlZeroMemory(&this->RequestPacket, sizeof(this->RequestPacket));

		READ_PACKET ReadPacket = { };

		ReadPacket.ProcessId = this->TargetProcessId;
		ReadPacket.Size = Size;
		ReadPacket.SourceAddress = SourceAddress;
		ReadPacket.TargetAddress = TargetAddress;

		this->RequestPacket.Type = RequestType::ReadMemory;
		this->RequestPacket.Buffer = &ReadPacket;
		this->RequestPacket.Status = STATUS_PENDING;

		SetEvent(this->UserEvent);
		WaitForSingleObject(this->KernelEvent,  1000 * 60); // 3 minutes

		return this->RequestPacket.Status;
	}

	template<typename T>
	T Read(UINT_PTR Address)
	{
		T Buffer = { };

		if (!NT_SUCCESS(Read((PVOID)Address, &Buffer, sizeof(T))))
		{
			RtlZeroMemory(&Buffer, sizeof(Buffer));
		}

		return Buffer;
	}

	NTSTATUS Write(PVOID SourceAddress, PVOID TargetAddress, SIZE_T Size)
	{
		RtlZeroMemory(&this->RequestPacket, sizeof(this->RequestPacket));

		WRITE_PACKET WritePacket = { };

		WritePacket.ProcessId = this->TargetProcessId;
		WritePacket.Size = Size;
		WritePacket.SourceAddress = SourceAddress;
		WritePacket.TargetAddress = TargetAddress;

		this->RequestPacket.Type = RequestType::WriteMemory;
		this->RequestPacket.Buffer = &WritePacket;
		this->RequestPacket.Status = STATUS_PENDING;

		SetEvent(this->UserEvent);
		WaitForSingleObject(this->KernelEvent,  1000 * 60); // 3 minutes

		return this->RequestPacket.Status;
	}

	template<typename T>
	NTSTATUS Write(UINT_PTR Address, T Buffer)
	{
		return Write(&Buffer, (PVOID)Address, sizeof(T));
	}

	NTSTATUS WriteToReadOnly(PVOID SourceAddress, PVOID TargetAddress, SIZE_T Size)
	{
		RtlZeroMemory(&this->RequestPacket, sizeof(this->RequestPacket));

		FORCE_WRITE_PACKET ForceWritePacket = { };

		ForceWritePacket.ProcessId = this->TargetProcessId;
		ForceWritePacket.Size = Size;
		ForceWritePacket.SourceAddress = SourceAddress;
		ForceWritePacket.TargetAddress = TargetAddress;

		this->RequestPacket.Type = RequestType::WriteToReadOnly;
		this->RequestPacket.Buffer = &ForceWritePacket;
		this->RequestPacket.Status = STATUS_PENDING;

		SetEvent(this->UserEvent);
		WaitForSingleObject(this->KernelEvent, 1000 * 60); // 3 minutes

		return this->RequestPacket.Status;
	}

	template<typename T>
	NTSTATUS WriteToReadOnly(UINT_PTR Address, T Buffer)
	{
		return WriteToReadOnly(&Buffer, (PVOID)Address, sizeof(T));
	}

};