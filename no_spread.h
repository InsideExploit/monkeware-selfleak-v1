#pragma once

void no_spread()
{
	if (features::ns_enabled_state == true)
	{
		Interface->Write<float>(get_weapon_info() + 0x88, features::spread);
		features::ns_disabled_state = true;
	}
	else if (features::ns_disabled_state == true)
	{
		Interface->Write<float>(get_weapon_info() + 0x88, 0.75);
		features::ns_disabled_state = false;
	}
}