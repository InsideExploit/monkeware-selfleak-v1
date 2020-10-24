#pragma once

enum class RequestType : int
{
	Unload,
	NewThread,
	MainModule,
	Module,
	ReadMemory,
	WriteMemory,
	WriteToReadOnly
};

typedef struct _INIT_PACKET
{
	PVOID RequestBuffer;
	HANDLE UserProcessId;
	WCHAR KernelEventName[0xFF];
	WCHAR UserEventName[0xFF];
	BOOLEAN IsInitialized;
} INIT_PACKET, * PINIT_PACKET;

typedef struct _REQUEST_PACKET
{
	RequestType Type;
	PVOID Buffer;
	NTSTATUS Status;
} REQUEST_PACKET, * PREQUEST_PACKET;

typedef struct _MAIN_MODULE_PACKET
{
	HANDLE ProcessId;
	PVOID Result;
} MAIN_MODULE_PACKET, * PMAIN_MODULE_PACKET;

typedef struct _MODULE_PACKET
{
	HANDLE ProcessId;
	WCHAR ModuleName[128];
	PVOID Result;
} MODULE_PACKET, * PMODULE_PACKET;

typedef struct _READ_PACKET
{
	HANDLE ProcessId;
	PVOID SourceAddress;
	PVOID TargetAddress;
	SIZE_T Size;
} READ_PACKET, * PREAD_PACKET;

typedef struct _WRITE_PACKET
{
	HANDLE ProcessId;
	PVOID SourceAddress;
	PVOID TargetAddress;
	SIZE_T Size;
} WRITE_PACKET, * PWRITE_PACKET;

typedef struct _FORCE_WRITE_PACKET
{
	HANDLE ProcessId;
	PVOID SourceAddress;
	PVOID TargetAddress;
	SIZE_T Size;
} FORCE_WRITE_PACKET, * PFORCE_WRITE_PACKET;
