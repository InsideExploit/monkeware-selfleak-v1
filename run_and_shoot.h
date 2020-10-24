#pragma once

void run_and_shoot()
{
    static bool getOrigRCX = true;
    static uint64_t origRCX = 0x0;
    static bool getOrigRCX40 = true;
    static uint64_t origRCX40 = 0x0;

    if (features::ras_enabled_state == true)
    {
        uint64_t rcx = Interface->Read<uint64_t>(MainModule + 0x68CEC90);
        rcx = Interface->Read<uint64_t>(rcx + 0x18);
        rcx = Interface->Read<uint64_t>(rcx);
        rcx = Interface->Read<uint64_t>(rcx + 0x30);
        rcx = Interface->Read<uint64_t>(rcx + 0x30);
        rcx = Interface->Read<uint64_t>(rcx + 0x50);
        rcx = Interface->Read<uint64_t>(rcx + 0x8);
        rcx = Interface->Read<uint64_t>(rcx + 0x148);
        uint64_t rcxW = Interface->Read<uint64_t>(rcx + 0x30);
        rcx = Interface->Read<uint64_t>(rcxW + 0x178);
        if (getOrigRCX)
        {
            origRCX = rcx;
            getOrigRCX = false;
        }
        if (getOrigRCX40)
        {
            origRCX40 = Interface->Read<uint64_t>(rcx + 0x40);
            getOrigRCX40 = false;
        }
        Interface->Write<uint64_t>(rcx + 0x40, 0x0);
        Interface->Write<uint8_t>(rcx + 0x80, 0x1);
        Interface->Write<uint64_t>(rcxW + 0x178, 0x0);

        features::ras_disabled_state = true;
    }
    else if (features::ras_disabled_state == true)
    {
        uint64_t rcx = Interface->Read<uint64_t>(MainModule + 0x68CEC90);
        rcx = Interface->Read<uint64_t>(rcx + 0x18);
        rcx = Interface->Read<uint64_t>(rcx);
        rcx = Interface->Read<uint64_t>(rcx + 0x30);
        rcx = Interface->Read<uint64_t>(rcx + 0x30);
        rcx = Interface->Read<uint64_t>(rcx + 0x50);
        rcx = Interface->Read<uint64_t>(rcx + 0x8);
        rcx = Interface->Read<uint64_t>(rcx + 0x148);
        rcx = Interface->Read<uint64_t>(rcx + 0x30);
        Interface->Write<uint64_t>(rcx + 0x178, origRCX);
        getOrigRCX = true;
        rcx = Interface->Read<uint64_t>(rcx + 0x178);
        Interface->Write<uint64_t>(rcx + 0x40, origRCX40);
        getOrigRCX40 = true;
        features::ras_disabled_state = false;
    }
}