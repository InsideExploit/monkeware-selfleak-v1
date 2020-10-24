#pragma once

void spoof_spectate()
{
	if (features::spectate_enabled_state == true)
	{
		Interface->Write<BYTE>(spoof_spectate_manager() + offsets::spoof, 1);
		features::spectate_disabled_state = true;
	}
	else if (features::spectate_disabled_state == true)
	{
		Interface->Write<BYTE>(spoof_spectate_manager() + offsets::spoof, 0);
		features::spectate_disabled_state = false;
	}
}