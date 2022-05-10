#pragma once

#include "UnityEngine/Vector3.hpp"

#include "GlobalNamespace/PlatformLeaderboardViewController.hpp"
#include "GlobalNamespace/SharedCoroutineStarter.hpp"
using namespace GlobalNamespace;

#include "custom-types/shared/coroutine.hpp"

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
        custom_types::Helpers::Coroutine WaitForScreen(QuestUI::FloatingScreen* panel, UnityEngine::Vector3 leaderboardPosition, GlobalNamespace::PlatformLeaderboardViewController* platformLeaderboardViewController);

        void Show(QuestUI::FloatingScreen* panelScreen,
        UnityEngine::Vector3 leaderboardPos, 
        PlatformLeaderboardViewController* leaderboardViewController);

        void Hide(QuestUI::FloatingScreen* panelScreen);
    };
}