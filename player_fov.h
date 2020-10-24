#pragma once

void player_fov()
{
	uintptr_t chain = NULL;

	chain = Interface->Read<uintptr_t>(fov_manager() + 0x10);


	if (features::pfov_enabled_state == true)
	{
		Interface->Write<float>(chain + 0xB38, features::player_fov);
		features::pfov_disabled_state = true;
	}
	else if (features::pfov_disabled_state == true)
	{
		Interface->Write<float>(chain + 0xB38, 1.506999969f);
		features::pfov_disabled_state = false;
	}
}