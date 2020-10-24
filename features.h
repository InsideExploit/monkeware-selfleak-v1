#pragma once

namespace features
{
	bool aim_enabled_state = false;
	bool team_aim_enabled_state = false;
	float aim_fov = 0;

	bool cav_enabled_state = false;
	bool cav_disabled_state = false;

	bool nr_enabled_state = false;
	bool nr_disabled_state = false;
	float recoil = 0;

	bool ns_enabled_state = false;
	bool ns_disabled_state = false;
	float spread = 0;

	bool pfov_enabled_state = false;
	bool pfov_disabled_state = false;
	float player_fov = 0;

	bool gfov_enabled_state = false;
	bool gfov_disabled_state = false;
	float gun_fov = 0;

	bool ras_enabled_state = false;
	bool ras_disabled_state = false;

	bool ladder_enabled_state = false;
	bool ladder_disabled_state = false;

	bool ua_state_enable = false;
	bool ua_state_disable = false;

	bool noclip_state_enable = false;
	bool noclip_state_disable = false;

	bool speed_state_enable = false;
	bool speed_state_disable = false;
	int player_speed = 0;

	bool firemode_state_enable = false;

	bool spectate_enabled_state = false;
	bool spectate_disabled_state = false;

	bool flash_enabled_state = false;

	bool knife_enabled_state = false;
	bool knife_disabled_state = false;
	float knife_distance = 0;

	bool ads_enabled_state = false;
	bool ads_disabled_state = false;

	bool patched_silent = false;
	bool unpatched_silent = false;

	bool knife_wall_enbaled = false;
	bool knife_wall_disabled = false;

	bool outlines_enabled_state = false;
	bool outlines_disabled_state = false;
	float outline_thickness = 0;
	float RGB[3];

	bool fullbright_enabled_state = false;

	bool glow_enabled_state = false;
	bool glow_disabled_state = false;
	float glow_RGB[3];
}