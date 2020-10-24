#pragma once

const char* firemode_options[] = { ("Full auto"), ("Burst 2"), ("Burst 3"), ("Single") };
static int firemode_setting = 0;

const char* key_options[] = { ("LBUTTON"), ("RBUTTON"), ("M5"), ("M4") };
static int key_setting = 0;
uintptr_t key = 0x0;

void set_key()
{
	if (key_setting == 0)
	{
		key = 0x01;
	}
	if (key_setting == 1)
	{
		key = 0x02;
	}
	if (key_setting == 2)
	{
		key = 0x05;
	}
	if (key_setting == 3)
	{
		key = 0x06;
	}
}

const char* speed_item[] = { ("None"), ("M4"),("M5"), ("V"), ("X"), ("J"), ("K"), ("Shift"), ("`") };
static int speed_bind = 0;
uintptr_t speed_key = 0;

void set_speed_bind()
{
    if (speed_bind == 0)
    {
        speed_key_state = false;
    }
    if (speed_bind == 1)
    {
        speed_key_state = true;
        speed_key = 0x06;
    }
    if (speed_bind == 2)
    {
        speed_key_state = true;
        speed_key = 0x05;
    }
    if (speed_bind == 3)
    {
        speed_key_state = true;
        speed_key = 0x56;
    }
    if (speed_bind == 4)
    {
        speed_key_state = true;
        speed_key = 0x58;
    }
    if (speed_bind == 5)
    {
        speed_key_state = true;
        speed_key = 0x4A;
    }
    if (speed_bind == 6)
    {
        speed_key_state = true;
        speed_key = 0x4B;
    }
    if (speed_bind == 7)
    {
        speed_key_state = true;
        speed_key = 0x10;
    }
    if (speed_bind == 8)
    {
        speed_key_state = true;
        speed_key = 0xC0;
    }
}

const char* noclip_item[] = { ("None"), ("M4"),("M5"), ("V"), ("X"), ("J"), ("K"), ("Shift"), ("`") };
static int noclip_bind = 0;
uintptr_t noclip_key = 0;

void set_noclip_bind()
{
    if (noclip_bind == 0)
    {
        noclip_key_state = false;
    }
    if (noclip_bind == 1)
    {
        noclip_key_state = true;
        noclip_key = 0x06;
    }
    if (noclip_bind == 2)
    {
        noclip_key_state = true;
        noclip_key = 0x05;
    }
    if (noclip_bind == 3)
    {
        noclip_key_state = true;
        noclip_key = 0x56;
    }
    if (noclip_bind == 4)
    {
        noclip_key_state = true;
        noclip_key = 0x58;
    }
    if (noclip_bind == 5)
    {
        noclip_key_state = true;
        noclip_key = 0x4A;
    }
    if (noclip_bind == 6)
    {
        noclip_key_state = true;
        noclip_key = 0x4B;
    }
    if (noclip_bind == 7)
    {
        noclip_key_state = true;
        noclip_key = 0x10;
    }
    if (noclip_bind == 8)
    {
        noclip_key_state = true;
        noclip_key = 0xC0;
    }
}