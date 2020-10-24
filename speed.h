#pragma once

void speed()
{
	if (features::speed_state_enable == true)
	{
		uintptr_t chain = event_manager();

		chain = Interface->Read<uintptr_t>(chain + 0x30);
		chain = Interface->Read<uintptr_t>(chain + 0x38);

		set_speed_bind();
		if (speed_key_state == true)
		{
			if (GetAsyncKeyState(speed_key))
			{
				Interface->Write<int>(chain + 0x58, features::player_speed);
			}
			else
			{
				Interface->Write<int>(chain + 0x58, 110);
			}
		}
		else
		{
			Interface->Write<int>(chain + 0x58, features::player_speed);
		}
		features::speed_state_disable = true;
	}
	else if (features::speed_state_disable == true)
	{
		uintptr_t chain = event_manager();

		chain = Interface->Read<uintptr_t>(chain + 0x30);
		chain = Interface->Read<uintptr_t>(chain + 0x38);

		Interface->Write<int>(chain + 0x58, 110);
		features::speed_state_disable = false;
	}
}