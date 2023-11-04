#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "Game.h"
#include "Entity.h"
#include "MenuConfig.hpp"
#include <iostream>
#include "View.hpp"

extern "C" {
#include "Features\Mouse.h"
#include "Entity.h"
}

#include "TF/Quaternion.h"
#include "TF/EulerAngle.h"

namespace AimControl
{
    inline int HotKey = VK_LMENU;
    inline float AimFov = 5;
    inline float Smooth = 0.7;
    inline Vec2 RCSScale = { 1.f,1.f };
    inline int RCSBullet = 1;
    inline std::vector<int> HotKeyList{ VK_LMENU, VK_LBUTTON, VK_RBUTTON, VK_XBUTTON1, VK_XBUTTON2, VK_CAPITAL, VK_LSHIFT, VK_LCONTROL };

    inline void SetHotKey(int Index)
    {
        HotKey = HotKeyList.at(Index);
    }

    inline void switchToggle()
    {
        MenuConfig::AimAlways = !MenuConfig::AimAlways;
    }

    inline void AimBot(const CEntity& Local, Vec3 LocalPos, Vec3 AimPos)
    {
        if (MenuConfig::ShowMenu)
            return;

        float Yaw, Pitch;
        float Distance, Norm;
        Vec3 OppPos, AimPos_;
        int ScreenCenterX = Gui.Window.Size.x / 2;
        int ScreenCenterY = Gui.Window.Size.y / 2;
        float TargetX = 0.f;
        float TargetY = 0.f;


        AimPos_ = Vec3(AimPos);

        OppPos = AimPos_ - LocalPos;
          
        if (MenuConfig::RecoilCorrection && GetAsyncKeyState(VK_LBUTTON)) {
            EulerAngle euler(-Local.Pawn.AimPunchAngle.y, Local.Pawn.AimPunchAngle.x * 0.7f, .0f);
            Quaternion q;  
            q.SetEulerAngle(euler);
            Vec3 opp;
            q.Mul(OppPos.x, OppPos.y, OppPos.z, opp.x, opp.y, opp.z);
            OppPos = Vec3(opp);
            AimPos_ = LocalPos + OppPos;
        }
        


        Distance = OppPos.Length();
        Yaw = atan2f(OppPos.y, OppPos.x) * 57.295779513 - Local.Pawn.ViewAngle.y;
        Pitch = -atan(OppPos.z / Distance) * 57.295779513 - Local.Pawn.ViewAngle.x;

        Norm = sqrt(pow(Yaw, 2) + pow(Pitch, 2));




        float halfFov = AimFov * 0.5f;

        Vec2 ScreenPos;
        gGame.View.WorldToScreen(Vec3(AimPos_), ScreenPos);

        if (Norm < halfFov)
        {
            if (ScreenPos.x > ScreenCenterX)
            {
                TargetX = -(ScreenCenterX - ScreenPos.x);
                if (Smooth != 0.0f) {
                    TargetX /= Smooth;
                }
                if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
            }
            if (ScreenPos.x < ScreenCenterX)
            {
                TargetX = ScreenPos.x - ScreenCenterX;
                if (Smooth != 0.0f) {
                    TargetX /= Smooth;
                }
                if (TargetX + ScreenCenterX < 0) TargetX = 0;
            }

            if (ScreenPos.y != 0)
            {
                if (ScreenPos.y > ScreenCenterY)
                {
                    TargetY = -(ScreenCenterY - ScreenPos.y);
                    if (Smooth != 0.0f) {
                        TargetY /= Smooth;
                    }
                    if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
                }

                if (ScreenPos.y < ScreenCenterY)
                {
                    TargetY = ScreenPos.y - ScreenCenterY;
                    if (Smooth != 0.0f) {
                        TargetY /= Smooth;
                    }
                    if (TargetY + ScreenCenterY < 0) TargetY = 0;
                }
            }




            if (!Smooth)
            {
                mouse_event(MOUSEEVENTF_MOVE, (DWORD)(TargetX), (DWORD)(TargetY), NULL, NULL);
                return;
            }

            TargetX /= 10;
            TargetY /= 10;
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
            mouse_event(MOUSEEVENTF_MOVE, TargetX, TargetY, NULL, NULL);
        }
    }
}