#pragma once

void long_knife()
{
	uintptr_t chain = event_manager();

	chain = Interface->Read<uintptr_t>(chain + 0x80);
	chain = Interface->Read<uintptr_t>(chain + 0x30);

	if (features::knife_enabled_state == true)
	{
		Interface->Write<Vector2>(chain + 0x60, { features::knife_distance, features::knife_distance });
		features::knife_disabled_state = true;
	}
	else if (features::knife_disabled_state == true)
	{
		Interface->Write<Vector2>(chain + 0x60, { 1.3,  1.3 });
		features::knife_disabled_state = false;
	}
}