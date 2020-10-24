#pragma once

bool wrote_fullbright = false;

void fullbright()
{
	if (features::fullbright_enabled_state == true)
	{
		if (wrote_fullbright == false)
		{
			uintptr_t chain = enviroment_manager();

			chain = Interface->Read<uintptr_t>(chain + 0xB8);
			Interface->Write<float>(chain + decrypt(0x80000000031F3F1, 0xFA55A7), 0); // Dont share, its private
			wrote_fullbright = true;
		}
	}
}