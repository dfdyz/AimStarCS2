#pragma once
#include <Windows.h>
#include "Utils/ProcessManager.hpp"

namespace Offset
{
	inline DWORD EntityList;
	inline DWORD Matrix;
	inline DWORD ViewAngle;
	inline DWORD LocalPlayerController;
	inline DWORD LocalPlayerPawn;
	inline DWORD ForceJump;
	inline DWORD GlobalVars;
	inline DWORD InventoryServices;

	struct
	{
		//m_iHealth
		DWORD Health = 0x32C;
		//m_iTeamNum
		DWORD TeamID = 0x3BF;
		//m_bPawnIsAlive
		DWORD IsAlive = 0x7C4;
		//m_hPlayerPawn
		DWORD PlayerPawn = 0x7BC;
		//m_iszPlayerName
		DWORD iszPlayerName = 0x610;
		//m_flDetectedByEnemySensorTime
		DWORD EnemySenesor = 0x13DC;
	} Entity;

	struct
	{
		DWORD BulletServices = 0x16B0;
		DWORD TotalHit = 0x40;

		//m_vOldOrigin
		DWORD Pos = 0x1224;
		//m_iMaxHealth
		DWORD MaxHealth = 0x328;
		//m_iHealth
		DWORD CurrentHealth = 0x32C;
		//m_pGameSceneNode
		DWORD GameSceneNode = 0x310;

		DWORD BoneArray = 0x1E0;

		//m_angEyeAngles
		DWORD angEyeAngles = 0x1510;
		//m_vecLastClipCameraPos
		DWORD vecLastClipCameraPos = 0x128C;
		//m_pClippingWeapon
		DWORD pClippingWeapon = 0x12A8;
		//m_iShotsFired
		DWORD iShotsFired = 0x1418;
		//m_flFlashDuration
		DWORD flFlashDuration = 0x1468;
		//m_aimPunchAngle
		DWORD aimPunchAngle = 0x1714;
		//m_aimPunchCache
		DWORD aimPunchCache = 0x1738;
		//m_iIDEntIndex
		DWORD iIDEntIndex = 0x153C;


		DWORD iTeamNum = 0x3BF;
		DWORD CameraServices = 0x10E0;
		DWORD iFovStart = 0x214;
		DWORD fFlags = 0x3C8;
		DWORD bSpottedByMask = 0x1630 + 0xC; // entitySpottedState + bSpottedByMask
	} Pawn;

	struct
	{
		DWORD RealTime = 0x00;
		DWORD FrameCount = 0x04;
		DWORD MaxClients = 0x10;
		DWORD IntervalPerTick = 0x14;
		DWORD CurrentTime = 0x2C;
		DWORD CurrentTime2 = 0x30;
		DWORD TickCount = 0x40;
		DWORD IntervalPerTick2 = 0x44;
		DWORD CurrentNetchan = 0x0048;
		DWORD CurrentMap = 0x0180;
		DWORD CurrentMapName = 0x0188;
	} GlobalVar;

	struct
	{
		DWORD m_hPawn = 0x5DC;
		DWORD m_pObserverServices = 0x10C0;
		DWORD m_hObserverTarget = 0x44;
		DWORD m_hController = 0x123C;
	} PlayerController;

	// Never have a try for external skin changer
	struct
	{
		//m_unMusicID
		DWORD MusicID = 0x40;
		//m_rank
		DWORD Rank = 0x44;
		//m_vecServerAuthoritativeWeaponSlots
		DWORD AuthoritativeWeaponSlots = 0x70;
	} Inventory;

	namespace Signatures
	{
		const std::string InventoryServices = "E8 ?? ?? ?? ?? 8B 45 D0 48 8B 55 D8";
		const std::string GlobalVars = "48 89 0D ?? ?? ?? ?? 48 89 41";
		const std::string EntityList = "48 8B 0D ?? ?? ?? ?? 48 89 7C 24 ?? 8B FA C1";
		const std::string LocalPlayerController = "48 8B 05 ?? ?? ?? ?? 48 85 C0 74 4F";
		const std::string ViewAngles = "48 8B 0D ?? ?? ?? ?? 48 8B 01 48 FF 60 30";
		const std::string ViewMatrix = "48 8D 0D ?? ?? ?? ?? 48 C1 E0 06";
		const std::string LocalPlayerPawn = "48 8D 05 ?? ?? ?? ?? C3 CC CC CC CC CC CC CC CC 48 83 EC ?? 8B 0D";
		const std::string ForceJump = "48 8B 05 ?? ?? ?? ?? 48 8D 1D ?? ?? ?? ?? 48 89 45";
	}

	// 一键更新基址
	bool UpdateOffsets();
}
