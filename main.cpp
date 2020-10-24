#include <iostream>
#include <Windows.h>

#include "includes.h"
#include "menu.h"

void init()
{
    printf("Setup : %lX\n", Interface->Setup());
    Interface->SetTargetProcessId((HANDLE)14892); // Put r6 pid here

    MainModule = Interface->GetMainModule();
    printf("MainModule : %llX\n", MainModule);
}

void feature_loop()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(16));//
        if (game_state() == 2)
        {
            cav_esp();
            player_fov();
            gun_fov();
            no_spread();
            no_recoil();
            fire_mode();
            no_flash();
            long_knife();
            fullbright();
            spoof_spectate();
            //run_and_shoot();
            speed();
            glow();
            ads();
        }
        else if (game_state() == 3)
        {
            cav_esp();
            player_fov();
            gun_fov();
            no_spread();
            no_recoil();
            fire_mode();
            no_flash();
            long_knife();
            fullbright();
            spoof_spectate();
            //run_and_shoot();
            noclip();
            speed();
            glow();
            ads();
        }
        unlock_all();
    }
}

void aim_loop()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(sleep_aim));
        if (features::aim_enabled_state == true)
        {
            set_key();
            aimbot();
        }
    }
}

int main(void)
{
    init();

    std::thread menu(draw_menu);
    std::thread features(feature_loop);
    std::thread aim(aim_loop);

    menu.detach();
    features.detach();
    aim.detach();

    while (1) {Sleep(10000);}
}