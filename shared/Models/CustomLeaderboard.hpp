#pragma once

#include "UnityEngine/Vector3.hpp"

#include "GlobalNamespace/PlatformLeaderboardViewController.hpp"
using namespace GlobalNamespace;

#include "questui/shared/CustomTypes/Components/FloatingScreen/FloatingScreen.hpp"
#include "HMUI/ViewController.hpp"
using namespace QuestUI;
using namespace HMUI;

namespace LeaderboardCore::Models {
    class CustomLeaderboard {
    public:
        HMUI::ViewController* m_PanelViewController;
        HMUI::ViewController* m_LeaderboardViewController;
    private:
        void Show(FloatingScreen* panelScreen, 
        UnityEngine::Vector3 leaderboardPos, 
        PlatformLeaderboardViewController* leaderboardViewController);

        void Hide(FloatingScreen* panelScreen);
    };
}