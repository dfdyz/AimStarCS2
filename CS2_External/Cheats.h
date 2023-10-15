#pragma once
#include "Game.h"
#include "Entity.h"
#include "AimBot.hpp"
#include "Radar/Radar.h"
#include "TriggerBot.h"
#include "Bunnyhop.hpp"

namespace Cheats
{
	void RenderCrossHair(ImDrawList* drawList) noexcept;

	void Menu();
	void RadarSetting(Base_Radar& Radar);
	void Run();
}

struct {
	ImFont* normal15px = nullptr;
} fonts;