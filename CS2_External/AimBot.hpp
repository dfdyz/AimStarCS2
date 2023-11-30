#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "Game.h"
#include "Entity.h"
#include "MenuConfig.hpp"
#include <iostream>
#include "View.hpp"
#include "Features/RCS.h"

extern "C" {
#include "Features\Mouse.h"
#include "Entity.h"
#include "TF/Quaternion.h"
}

#define PI 3.1415926535f

namespace AimControl
{
    inline int HotKey = VK_LMENU;
    inline float AimFov = 5;
    inline float SmoothX = 2.0f;
    inline float SmoothY = 2.0f;
    inline Vec2 RCSScale = { 1.f,1.f };
    inline std::vector<int> HotKeyList{ VK_LMENU, VK_LBUTTON, VK_RBUTTON, VK_XBUTTON1, VK_XBUTTON2, VK_CAPITAL, VK_LSHIFT, VK_LCONTROL };
    inline Vec2 _Angles = { 0,0 };
    inline Vec2 Angles = { 0,0 };

    inline void SetHotKey(int Index)
    {
        HotKey = HotKeyList.at(Index);
    }

    inline void switchToggle()
    {
        MenuConfig::AimAlways = !MenuConfig::AimAlways;
    }

    inline void AimBot(const CEntity& Local, Vec3 LocalPos, Vec3 &AimPos)
    {
        if (MenuConfig::ShowMenu)
            return;

        float Yaw, Pitch;
        float Distance, Norm;
        Vec3 OppPos;
        int ScreenCenterX = Gui.Window.Size.x / 2;
        int ScreenCenterY = Gui.Window.Size.y / 2;
        float TargetX = 0.f;
        float TargetY = 0.f;
        Quaternion q;

        OppPos = AimPos - LocalPos;

        if (MenuConfig::RCS) {
            //RCS::GetAngles(Local, Angles);
            //_Angles = Vec2(Angles);
            RCS::Run(Local, Angles, true);

            q.SetEulerAngle(
                -Angles.y / 180.f * PI * RCSScale.y,
                Angles.x / 180.f * PI * RCSScale.x,
                .0f);
            Vec3 opp;
            q.Mul(OppPos.x, OppPos.y, OppPos.z, opp.x, opp.y, opp.z);
            OppPos = Vec3(opp);
            AimPos = Vec3(LocalPos + OppPos);
        }

        Distance = sqrt(pow(OppPos.x, 2) + pow(OppPos.y, 2));

        Yaw = atan2f(OppPos.y, OppPos.x) * 57.295779513 - Local.Pawn.ViewAngle.y;
        Pitch = -atan(OppPos.z / Distance) * 57.295779513 - Local.Pawn.ViewAngle.x;
        Norm = sqrt(pow(Yaw, 2) + pow(Pitch, 2));

        Vec2 ScreenPos;
        gGame.View.WorldToScreen(Vec3(AimPos), ScreenPos);

        if (Norm < AimFov)
        {
            // Shake Fixed by @Sweely
            if (ScreenPos.x != ScreenCenterX)
            {
                TargetX = (ScreenPos.x > ScreenCenterX) ? -(ScreenCenterX - ScreenPos.x) : ScreenPos.x - ScreenCenterX;
                TargetX /= SmoothX != 0.0f ? SmoothX : 1.5f;
                TargetX = (TargetX + ScreenCenterX > ScreenCenterX * 2 || TargetX + ScreenCenterX < 0) ? 0 : TargetX;
            }

            if (ScreenPos.y != 0)
            {
                if (ScreenPos.y != ScreenCenterY)
                {
                    TargetY = (ScreenPos.y > ScreenCenterY) ? -(ScreenCenterY - ScreenPos.y) : ScreenPos.y - ScreenCenterY;
                    TargetY /= SmoothY != 0.0f ? SmoothY : 1.5f;
                    TargetY = (TargetY + ScreenCenterY > ScreenCenterY * 2 || TargetY + ScreenCenterY < 0) ? 0 : TargetY;
                }
            }

            // Dynamic AimSmooth based on distance
            float DistanceRatio = Norm / AimFov; // Calculate the distance ratio
            float SpeedFactor = 1.0f + (1.0f - DistanceRatio); // Determine the speed factor based on the distance ratio

            if (SmoothX) {
                TargetX /= (SmoothX * SpeedFactor);
                if (fabs(TargetX) < 1)
                {
                    if (TargetX > 0)
                    {
                        TargetX = 1;
                    }
                    if (TargetX < 0)
                    {
                        TargetX = -1;
                    }
                }
            }
            else
            {
                TargetY /= (SmoothY * SpeedFactor);
                if (fabs(TargetY) < 1)
                {
                    if (TargetY > 0)
                    {
                        TargetY = 1;
                    }
                    if (TargetY < 0)
                    {
                        TargetY = -1;
                    }
                }
            }
         
            mouse_event(MOUSEEVENTF_MOVE, (DWORD)(TargetX), (DWORD)(TargetY), NULL, NULL);
        }
    }
}