#pragma once

uintptr_t decrypt(uintptr_t encrypted, uintptr_t key)
{
	encrypted = __ROL8__(encrypted, -0x5FA);
	encrypted = encrypted - 0xC0FFEE;
	encrypted = encrypted / 3;
	encrypted = encrypted >> 2;

	return encrypted ^ key;
}