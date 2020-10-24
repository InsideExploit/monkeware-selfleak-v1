#pragma once

void no_flash()
{
	if (features::flash_enabled_state == true)
	{
		uintptr_t chain = event_manager();

		chain = Interface->Read<uintptr_t>(chain + 0x30);
		chain = Interface->Read<uintptr_t>(chain + 0x28);

		Interface->Write<uint8_t>(chain + 0xA0, 2);
	}
}