#pragma once

void cav_esp()
{
    if (features::cav_enabled_state == true)
    {
        for (int i = 0; i < GetEntityCount(); i++)
        {
            auto entityObject = GetEntityByID(i);
            entityObject = DecryptEntityInfo(entityObject);

            auto entityInfo = Interface->Read<uint64_t>(entityObject + 0x18);
            entityInfo = Interface->Read<uint64_t>(entityInfo + 0xD8);

            for (uint32_t curCo = 0x80; curCo < 0xF0; curCo += 4)
            {
                auto marker = Interface->Read<uint64_t>(entityInfo + curCo);
                if (marker == 0) continue;

                auto markerCheck = Interface->Read<uint64_t>(marker);
                if (markerCheck != (MainModule + offsets::vt_marker)) continue;
                Interface->Write<uint8_t>(marker + offsets::cav, 0x85);
            }
        }
    }
}