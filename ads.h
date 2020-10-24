#pragma once

void ads()
{
	if (features::ads_enabled_state == true)
	{
		auto chain = Interface->Read<uintptr_t>(get_localplayer() + 0x90);
		chain = Interface->Read<uintptr_t>(chain + 0x70) + 0x384;
		Interface->Write<BYTE>(chain, 0);
		features::ads_disabled_state = true;
	}
	else if (features::ads_disabled_state == true)
	{
		auto chain = Interface->Read<uintptr_t>(get_localplayer() + 0x90);
		chain = Interface->Read<uintptr_t>(chain + 0x70) + 0x384;
		Interface->Write<BYTE>(chain, 1);
		features::ads_disabled_state = false;
	}
}