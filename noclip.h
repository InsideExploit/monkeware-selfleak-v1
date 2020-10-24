	#pragma once

void noclip()
{
	if (features::noclip_state_enable == true)
	{
		uintptr_t chain = Interface->Read<uintptr_t>(noclip_manager() +0x128);
		chain = Interface->Read<uintptr_t>(chain + 0x10);

		set_noclip_bind();
		if (noclip_key_state == true)
		{
			if (GetAsyncKeyState(noclip_key))
			{
				Interface->Write<float>(chain + 0x700, -1);
			}
			else
			{
				Interface->Write<float>(chain + 0x700, 0.0003051850945f);
			}
		}
		else
		{
			Interface->Write<float>(chain + 0x700, -1);
		}
		features::noclip_state_disable = true;
	}
	else if (features::noclip_state_disable == true)
	{
		uintptr_t chain = Interface->Read<uintptr_t>(noclip_manager() + 0x128);
		chain = Interface->Read<uintptr_t>(chain + 0x10);

		Interface->Write<float>(chain + 0x700, 0.0003051850945f);
		features::noclip_state_disable = false;
	}
}