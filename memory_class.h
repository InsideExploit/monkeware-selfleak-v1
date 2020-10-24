#pragma once

/// <summary>
/// Class containing memory functions
/// </summary>
class memory_class
{
public:
    /// <summary>
    /// Base address of the target program
    /// </summary>
    uint64_t target_base = 0x0;

    /// <summary>
    /// Initializes the memory class
    /// </summary>
    /// <returns>true = success false = fail</returns>
    inline bool init_mem()
    {
        //system("cls");
        //printf("Init Memory... \n");

        if (get_pid())
        {
            //printf("PID: %d \n", target_pid);

            if (get_module())
            {
                //printf("Module: %d \n", target_base);

                return true;
            }
        }

        return false;
    }

    /// <summary>
    /// Grabs the process identifier of the target program
    /// </summary>
    /// <returns>PID = success 0 = fail</returns>
    inline uint32_t get_pid()
    {
        PROCESSENTRY32 process_info;

        HANDLE process_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
        if (process_snapshot == INVALID_HANDLE_VALUE)
            return 0;

        Process32First(process_snapshot, &process_info);
        if (!strcmp(process_info.szExeFile, target_name.c_str()))
        {
            CloseHandle(process_snapshot);
        }

        while (Process32Next(process_snapshot, &process_info))
        {
            if (!strcmp(process_info.szExeFile, target_name.c_str()))
            {
                CloseHandle(process_snapshot);
            }
        }

        target_pid = (uint32_t)process_info.th32ProcessID;
        return target_pid;
    }

    /// <summary>
    /// Grabs target handle and base address
    /// </summary>
    /// <returns>BASE = success 0 = fail</returns>
    inline uint64_t get_module()
    {
        HMODULE h_modules[1024];
        DWORD pcb_needed;

        target_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, target_pid);

        if (K32EnumProcessModules(target_handle, h_modules, sizeof(h_modules), &pcb_needed))
        {
            for (unsigned int i = 0; i < (pcb_needed / sizeof(HMODULE)); i++)
            {
                TCHAR module_name[MAX_PATH];
                if (GetModuleFileNameEx(target_handle, h_modules[i], module_name, sizeof(module_name) / sizeof(TCHAR)))
                {
                    std::string str_module_name = module_name;
                    if (str_module_name.find(target_name) != std::string::npos)
                    {
                        target_base = (uint64_t)h_modules[i];
                        return target_base;
                    }
                }
            }
        }

        return 0;
    }

    /// <summary>
    /// Template for reading memory from the target process
    /// </summary>
    /// <typeparam name="T">Type of memory to read</typeparam>
    /// <param name="address">Address to read inside of target</param>
    /// <returns>Buffer returned from ReadProcessMemory</returns>
    template<typename T>
    T read(uintptr_t address)
    {
        T buffer;
        ReadProcessMemory(target_handle, (LPCVOID)address, &buffer, sizeof(T), NULL);
        return buffer;
    }

    /// <summary>
    /// Template for writing memory into the target process
    /// </summary>
    /// <typeparam name="T">Type of memory to write</typeparam>
    /// <param name="address">Address to write buffer into</param>
    /// <param name="buffer">What to write into targeted address</param>
    template<typename T>
    void write(uintptr_t address, T buffer)
    {
        WriteProcessMemory(target_handle, (LPVOID)address, &buffer, sizeof(buffer), NULL);
    }

private:
    uint32_t    target_pid = 0x0;
    HANDLE      target_handle = 0x0;

    std::string target_name = "RainbowSix.exe";
};


/// <summary>
/// Handler of memory class
/// </summary>
memory_class memory;