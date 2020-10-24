#pragma once


uintptr_t game_manager()
{
    return Interface->Read<uintptr_t>(MainModule + decrypt(offsets::game_manager, custom_keys::game_manager_key));
}

uintptr_t profile_manager()
{
    return Interface->Read<uintptr_t>(MainModule + decrypt(offsets::profile_manager, custom_keys::profile_manager_key));
}

uintptr_t fov_manager()
{
    return Interface->Read<uintptr_t>(MainModule + decrypt(offsets::fov_manager, custom_keys::fov_manager_key));
}

uintptr_t network_manager()
{
    return Interface->Read<uintptr_t>(MainModule + decrypt(offsets::network_manager, custom_keys::network_manager_key));
}

uintptr_t enviroment_manager()
{
    return Interface->Read<uintptr_t>(MainModule + offsets::enviroment_manager);
}

uintptr_t round_manager()
{
    return Interface->Read<uintptr_t>(MainModule + ((decrypt(offsets::round_manager, custom_keys::round_manager_key) - 0xC4F) + 0x4DA8));
}

uintptr_t spoof_spectate_manager()
{
    return Interface->Read<uintptr_t>(MainModule + offsets::spoof_spectate_manager);
}

uintptr_t noclip_manager()
{
    return Interface->Read<uintptr_t>(MainModule + offsets::noclip_manager);
}

int game_state()
{
    return Interface->Read<int>(round_manager() + 0x300);
}

uint64_t get_localplayer()
{
    uint64_t local = Interface->Read<uint64_t>(profile_manager() + 0x88);
    local = Interface->Read<uint64_t>(local);
    local = Interface->Read<uint64_t>(local + 0x28);
    local += 0xBADD3F9015EF5524;
    local ^= 0x23;
    local += 0xB0EB703322DA824D;

    return local;
}

uint64_t get_weapon_info()
{
    uint64_t weaponInfo = Interface->Read<uint64_t>(get_localplayer() + 0x90);
    weaponInfo = Interface->Read<uint64_t>(weaponInfo + 0x70);
    weaponInfo = Interface->Read<uint64_t>(weaponInfo + 0x288);
    weaponInfo = __ROL8__(weaponInfo, 0x1D);
    weaponInfo -= 0x49;
    weaponInfo ^= 0xC07C346E918191F1;

    return weaponInfo;
}

uintptr_t event_manager()
{
    uintptr_t chain = NULL;

    chain = Interface->Read<uintptr_t>(get_localplayer() + 0x30);

    chain ^= 0x48;
    chain += 0x5364B35667A05F5B;

    return __ROL8__(chain, 0x2D);
}

uint64_t get_entity_list()
{
    uint64_t entityList = Interface->Read<uintptr_t>(game_manager() + 0xE0);
    entityList ^= 0x53;
    entityList += 0xEEBD43B91E3D5D54;
    entityList ^= 0x1FEC13843E78A654;

    return entityList;
}