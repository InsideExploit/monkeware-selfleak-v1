#pragma once

std::vector<uint64_t> entityList = {};

uint64_t GetEntityList()
{
	 uint64_t entityList = Interface->Read<uint64_t>(game_manager() + 0xE0);
	entityList ^= 0x53;
	entityList += 0xEEBD43B91E3D5D54;
	entityList ^= 0x1FEC13843E78A654;

	return entityList;
}

int GetEntityCount()
{
	uint64_t entityCount = Interface->Read<uint64_t>(game_manager() +0xE8);
	entityCount ^= 0x53;
	entityCount += 0xEEBD43B91E3D5D54;
	entityCount ^= 0x1FEC13843E78A654;
	int count = (int)(entityCount ^ 0x18C0000000);

	return count;
}

uint64_t GetEntityByID(int id)
{
	uint64_t entityList = GetEntityList();
	if (!entityList)
		return NULL;

	uint64_t entity = Interface->Read<uint64_t>(entityList + (sizeof(PVOID) * id));
	if (!entity)
		return NULL;

	return entity;
}

uint64_t DecryptEntityInfo(uint64_t entity)
{
	uint64_t info = Interface->Read<uint64_t>(entity + 0x50);
	info = __ROL8__(info, 1);
	info -= 0x53;
	info = info ^ 0x84B4E3BD4F9014AF;

	return info;
}

inline BYTE entity_team(uint64_t entity)
{
	uint64_t teamInfo = Interface->Read<uint64_t>(entity + 0xD0);
	teamInfo = Interface->Read<uint64_t>(teamInfo + 0x98);
	teamInfo = __ROL8__(teamInfo, 0x33);
	teamInfo += 0xDE627E1C01E6C58F;
	teamInfo = __ROL8__(teamInfo, 0x2B);
	BYTE team = Interface->Read<BYTE>(teamInfo + 0x30);

	return team;
}

inline void set_entity_team(uint64_t entity, BYTE team)
{
	uint64_t teamInfo = Interface->Read<uint64_t>(entity + 0xD0);
	teamInfo = Interface->Read<uint64_t>(teamInfo + 0x98);
	teamInfo = __ROL8__(teamInfo, 0x33);
	teamInfo += 0xDE627E1C01E6C58F;
	teamInfo = __ROL8__(teamInfo, 0x2B);
	Interface->Write<BYTE>(teamInfo + 0x30, team);
}

inline int32_t entity_health(uint64_t entity)
{
	uint64_t tmp = DecryptEntityInfo(entity);
	tmp = Interface->Read<uint64_t>(tmp + 0x18);
	tmp = Interface->Read<uint64_t>(tmp + 0xD8);
	tmp = Interface->Read<uint64_t>(tmp + 0x8);

	return Interface->Read<int>(tmp + 0x170);
}

inline Vector3 entity_bone(uint64_t entity, uint32_t bone)
{
	uint64_t tmp = DecryptEntityInfo(entity);

	return Interface->Read<Vector3>(tmp + (uint64_t)bone);
}

bool PopulateEntityList(std::vector<uint64_t>& players)
{
	BYTE localTeam = entity_team(get_localplayer());

	int size = GetEntityCount();

	if (size > 255)
		return false;

	entityList.resize(size);

	for (int i = 0; i < size; i++)
	{
		uint64_t player = GetEntityByID(i);

		if (player == 0)
			continue;

		if (entity_health(player) <= 20)
			continue;

		if (player == get_localplayer())
			continue;

		if (entity_team(player) == localTeam)
			continue;

		players.at(i) = player;
	}
	return true;
}

bool IsEnemy(uint64_t entity)
{
	if (entity == 0) return false;

	if (get_localplayer() == entity) return false;

	if (features::team_aim_enabled_state == false)
	{
		if (entity_team(get_localplayer()) == entity_team(entity)) return false; //Comment out if you want this to work for teamates/NPC's
	}

	return true;
}

// --- Camera Functions

Vector3 view_translation;

inline uint64_t game_camera()
{
	uint64_t tmp = Interface->Read<uint64_t>(profile_manager() +0x88);
	tmp = Interface->Read<uint64_t>(tmp + 0x0);
	tmp = Interface->Read<uint64_t>(tmp + 0x218);
	tmp = Interface->Read<uint64_t>(tmp + 0x410);

	return tmp;
}

inline Vector3 GetViewRight()
{
	return Interface->Read<Vector3>(game_camera() + 0x7A0);
}

inline Vector3 GetViewUp()
{
	return Interface->Read<Vector3>(game_camera() + 0x7B0);
}

inline Vector3 GetViewForward()
{
	return Interface->Read<Vector3>(game_camera() + 0x7C0);
}

inline Vector3 GetViewTranslation()
{
	return Interface->Read<Vector3>(game_camera() + 0x7D0);
}

float GetViewFovX()
{
	return  Interface->Read<float>(game_camera() + 0x7E0);
}

float GetViewFovY()
{
	return  Interface->Read<float>(game_camera() + 0x7F4);
}

bool WorldToScreen(Vector3 position, Vector2& Screen)
{
	uint64_t cam = game_camera();
	Vector3 temp = position - GetViewTranslation();
	float x = temp.Dot(GetViewRight());
	float y = temp.Dot(GetViewUp());
	float z = temp.Dot(GetViewForward() * -1.f);

	int width = 1920;
	int height = 1080;

	Screen.x = (width / 2.f) * (1.f + x / GetViewFovX() / z);
	Screen.y = (height / 2.f) * (1.f - y / GetViewFovY() / z);

	return z >= 1.0f ? true : false;
}

Vector4 CalculateQuaternion(Vector3 euler)
{
	Vector4 result{};

	auto yaw = (euler.z * 0.01745329251f) * 0.5f;
	auto sy = std::sin(yaw);
	auto cy = std::cos(yaw);

	auto roll = (euler.x * 0.01745329251f) * 0.5f;
	auto sr = std::sin(roll);
	auto cr = std::cos(roll);

	constexpr auto sp = 0.f;
	constexpr auto cp = 1.f;

	result.x = cy * sr * cp - sy * cr * sp;
	result.y = cy * cr * sp + sy * sr * cp;
	result.z = sy * cr * cp - cy * sr * sp;
	result.w = cy * cr * cp + sy * sr * sp;

	return result;
}

void SetAngles(Vector3 angles)
{
	Vector4 quat = CalculateQuaternion(angles);

	uint64_t holder = DecryptEntityInfo(get_localplayer());
	uint64_t skeleton = Interface->Read<uint64_t>(holder + 0x1270);

	Interface->Write<Vector4>(skeleton + 0xC0, quat);
}

void set_gun_angles(Vector3 angles)
{
	Interface->Write<Vector3>(get_weapon_info() + 0x148, angles);
}

Vector3 CalcAngle(Vector3 enemyPos, Vector3 cameraPos)
{
	Vector3 dir = enemyPos - cameraPos;
	float x = asinf(dir.z / dir.Length()) * 57.2957795131f;

	float z = atanf(dir.y / dir.x) * 57.2957795131f;

	if (dir.x >= 0.f) z += 180.f;
	if (x > 179.99f) x -= 360.f;
	else if (x < -179.99f) x += 360.f;

	return Vector3(x, 0.f, z + 90.f);
}

uint64_t GetClosestEntityToCrosshair()
{
	float oDist = FLT_MAX;
	float nDist = 0;
	uint64_t cur = NULL;
	uint64_t target = NULL;
	Vector2 screenPos;
	Vector2 screenCenter = { (1920 / 2), (1080 / 2) };
	float fov = features::aim_fov;

	for (int i = 0; i < GetEntityCount(); i++)
	{
		cur = GetEntityByID(i);
		if (cur == 0) continue;

		if (WorldToScreen(entity_bone(cur, entity_bones::head), screenPos))
		{
			nDist = DistanceVec2(screenCenter, screenPos);

			if (nDist < fov && nDist < oDist)
			{
				oDist = nDist;
				target = cur;
			}
		}
	}
	return target;
}

uint64_t GetClosestEntityToHead()
{
	float oDist = FLT_MAX;
	float nDist = 0;
	uint64_t cur = NULL;
	uint64_t target = NULL;
	Vector2 screenPos;

	for (int i = 0; i < GetEntityCount(); i++)
	{
		cur = GetEntityByID(i);

		if (!IsEnemy(cur))
			continue;

		if (WorldToScreen(entity_bone(cur, entity_bones::head), screenPos))
		{
			nDist = DistanceVec3(entity_bone(get_localplayer(), entity_bones::head), entity_bone(cur, entity_bones::head));

			if (nDist < oDist)
			{
				oDist = nDist;
				target = cur;
			}
		}
	}

	return target;
}

inline void aimbot()
{
	uint64_t target = GetClosestEntityToCrosshair(); if (!IsEnemy(target)) return;
	Vector3 angles = CalcAngle(entity_bone(target, entity_bones::head), GetViewTranslation()); angles.Clamp();
	if (GetAsyncKeyState(key))
	{
		SetAngles(angles);
	}
}

inline Vector3 clamp_angles(Vector3 angles)
{
	Vector3 clamped = angles;

	if (clamped.y > 179.f)
		clamped.y -= 360.f;

	else if (clamped.y < -179.f)
		clamped.y += 360.f;

	if (clamped.z > 179.f)
		clamped.z -= 360.f;

	else if (clamped.z < -179.f)
		clamped.z += 360.f;

	if (clamped.y < -89.f)
		clamped.y = -89.f;

	if (clamped.y > 89.f)
		clamped.y = 89.f;

	while (clamped.z < -179.0f)
		clamped.z += 360.0f;

	while (clamped.z > 179.0f)
		clamped.z -= 360.0f;

	return clamped;
}