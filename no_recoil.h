#pragma once

void recoil_multiplier()
{
	uint64_t weapon = Interface->Read<uint64_t>(get_localplayer() + 0x90);
	uint64_t curWeapon = Interface->Read<uint64_t>(weapon + 0x70);
	uint64_t arrayToSingle = Interface->Read<uint64_t>(curWeapon + 0x258);
	arrayToSingle = Interface->Read<uint64_t>(arrayToSingle);
	uint64_t curWeaponPreset = Interface->Read<uint64_t>(arrayToSingle + 0x140);
	curWeaponPreset = Interface->Read<uint64_t>(curWeaponPreset);
	Interface->Write<float>(curWeaponPreset + 0x70, 0.f); //Pull
	Interface->Write<float>(curWeaponPreset + 0x74, 0.f); //Kick
}

void no_recoil()
{
	if (features::nr_enabled_state == true)
	{
		Interface->Write<BYTE>(get_weapon_info() + 0x198, 0);
		Interface->Write<Vector2>(get_weapon_info() + 0x18C, { features::recoil, features::recoil });
		recoil_multiplier();
		features::nr_disabled_state = true;
	}
	else if (features::nr_disabled_state == true)
	{
		Interface->Write<BYTE>(get_weapon_info() + 0x198, 0);
		features::nr_disabled_state = false;
	}
}