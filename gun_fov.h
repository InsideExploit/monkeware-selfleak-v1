#pragma once

void gun_fov()
{
	uintptr_t chain = NULL;

	chain = Interface->Read<uintptr_t>(fov_manager() + 0x10);

	if (features::gfov_enabled_state == true)
	{
		Interface->Write<float>(chain + 0xB3C, features::gun_fov);
		features::gfov_disabled_state = true;
	}
	else if (features::gfov_disabled_state == true)
	{
		Interface->Write<float>(chain + 0xB3C, 0.8726646304f);
		features::gfov_disabled_state = false;
	}
}