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
    inline bool ImmunityCheck = true;

    inline int Mode = 0;

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
        float Distance, Norm, Length;
        Vec3 OppPos;
        int ScreenCenterX = Gui.Window.Size.x / 2;
        int ScreenCenterY = Gui.Window.Size.y / 2;
        float TargetX = 0.f;
        float TargetY = 0.f;
        Quaternion q;

        OppPos = AimPos - LocalPos;

        Distance = sqrt(OppPos.x * OppPos.x + OppPos.y * OppPos.y);
        Length = sqrt(Distance * Distance + OppPos.z * OppPos.z);
        if (MenuConfig::RCS) {
            //RCS::GetAngles(Local, Angles);
            //_Angles = Vec2(Angles);
            //RCS::Run(Local, Angles, true);

            float rad = Angles.x * RCSScale.x / 180.f * PI;
            float si = sinf(rad);
            float co = cosf(rad);

            float z_ = OppPos.z * co + Distance * si;
            float d_ = (Distance * co - OppPos.z * si) / Distance;

            rad = -Angles.y * RCSScale.y / 180.f * PI;
            si = sinf(rad);
            co = cosf(rad);

            float x_ = (OppPos.x * co - OppPos.y * si) * d_;
            float y_ = (OppPos.x * si + OppPos.y * co) * d_;

            OppPos = Vec3{ x_, y_, z_ };

            AimPos = LocalPos + OppPos;
        }

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
                TargetX /= SmoothX != 0.0f ? SmoothX + 1.f : 1.5f;
                TargetX = (TargetX + ScreenCenterX > ScreenCenterX * 2 || TargetX + ScreenCenterX < 0) ? 0 : TargetX;
            }

            if (ScreenPos.y != 0)
            {
                if (ScreenPos.y != ScreenCenterY)
                {
                    TargetY = (ScreenPos.y > ScreenCenterY) ? -(ScreenCenterY - ScreenPos.y) : ScreenPos.y - ScreenCenterY;
                    TargetY /= SmoothY != 0.0f ? SmoothY + 1.f : 1.5f;
                    TargetY = (TargetY + ScreenCenterY > ScreenCenterY * 2 || TargetY + ScreenCenterY < 0) ? 0 : TargetY;
                }
            }

            //Dynamic AimSmooth based on distance
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
            if (SmoothY)
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
         
            mouse_event(MOUSEEVENTF_MOVE, TargetX, TargetY, NULL, NULL);
        }
    }
}