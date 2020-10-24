#pragma once

void glow()
{
    if (features::glow_enabled_state == true)
    {
        uintptr_t glow = Interface->Read<uintptr_t>(enviroment_manager() + 0xB8);

        Interface->Write<Vector3>(glow + 0xD0, { features::RGB[0], features::RGB[1], features::RGB[2] });
        Interface->Write<Vector4>(glow + 0x110, { 255, 0.5, 999, 999 });

        features::glow_disabled_state = true;
    }
    else if (features::glow_disabled_state == true)
    {
        uintptr_t glow = Interface->Read<uintptr_t>(enviroment_manager() + 0xB8);

        Interface->Write<Vector3>(glow + 0xD0, { 0.5372549295, 0.5372549295, 0.5372549295 });
        Interface->Write<Vector4>(glow + 0x110, { 0, 0, 0, 0 });

        features::glow_disabled_state = false;
    }
}