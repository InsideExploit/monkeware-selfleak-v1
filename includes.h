#pragma once

enum entity_bones
{
	head = 0x1070,
	spine = 0x1090,
	neck = 0x10F0
};


bool noclip_key_state = false;
bool speed_key_state = false;
int sleep_aim = 1;

#include <d3d9.h>
#include <dinput.h>
#include <tchar.h>
#include <WinUser.h>
#include <Psapi.h>
#include <thread>
#include <string>
#include <cstdarg>
#include <cmath>
#include <chrono>
#include <vector>
#include <emmintrin.h>
#include <cstdlib>
#include <stdlib.h>
#include <regex>
#include <string>
#include <conio.h>
#include <TlHelp32.h>
#include <math.h>
#include <cmath>
#include <Windows.h>
#include <synchapi.h>
#include <thread>
#include <ntstatus.h>
#include <time.h>
#include <random>

#include "interface.hpp"

const auto Interface = new KernelInterface;
uintptr_t MainModule;

#include "xor.h"
#include "defs.h"
#include "features.h"
#include "keybind.h"
#include "memory.h"
#include "random.h"
#include "rand.h"
#include "encryption.h"
#include "monkeware_keys.h"
#include "offsets.h"
#include "vector.h"
#include "rainbow_six.h" //
#include "no_recoil.h" //
#include "no_spread.h" //
#include "gun_fov.h" //
#include "run_and_shoot.h" //
#include "fullbright.h" //
#include "player_fov.h" //
#include "unlock_all.h"
#include "glow.h" //
#include "noclip.h" //
#include "flash.h" //
#include "firemode.h" //
#include "long_knife.h" //
#include "speed.h" //
#include "spectate.h" //
#include "ads.h" //
#include "knife_walls.h" //
#include "aimbot.h" //
#include "cav.h"//

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx9.h"

#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib, "d3d9.lib")