#pragma once

void fire_mode()
{
	uintptr_t chain = NULL;

	chain = Interface->Read<uintptr_t>(get_localplayer() + 0x90);
	chain = Interface->Read<uintptr_t>(chain + 0x70) + 0x120;

	if (features::firemode_state_enable == true)
	{
		Interface->Write<int>(chain, 0);
	}
}