#pragma once

#include "UnityEngine/Vector3.hpp"

#include "GlobalNamespace/PlatformLeaderboardViewController.hpp"
using namespace GlobalNamespace;

#include "questui/shared/CustomTypes/Components/FloatingScreen/FloatingScreen.hpp"
#include "HMUI/ViewController.hpp"
#include "HMUI/ViewController_AnimationType.hpp"
#include "HMUI/Screen.hpp"
using namespace QuestUI;
using namespace HMUI;

namespace LeaderboardCore::Models {
    class CustomLeaderboard {
    public:
        HMUI::ViewController* m_PanelViewController;
        HMUI::ViewController* m_LeaderboardViewController;
    private:
        void Show(HMUI::Screen* panelScreen, 
        UnityEngine::Vector3 leaderboardPos, 
        PlatformLeaderboardViewController* leaderboardViewController);

        void Hide(HMUI::Screen* panelScreen);
    };
}