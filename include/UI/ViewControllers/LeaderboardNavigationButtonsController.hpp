#pragma once

#include "questui/shared/CustomTypes/Components/FloatingScreen/FloatingScreen.hpp"
#include "custom-types/shared/macros.hpp"
using namespace QuestUI;

#include "sombrero/shared/FastVector3.hpp"
#include "UnityEngine/Transform.hpp"
#include "HMUI/ViewController.hpp"
using namespace Sombrero;
using namespace UnityEngine;

#include "GlobalNamespace/IPreviewBeatmapLevel.hpp"
#include "GlobalNamespace/IDifficultyBeatmap.hpp"
#include "HMUI/ViewController.hpp"
using namespace GlobalNamespace;

#include "Models/CustomLeaderboard.hpp"
#include "shared/Interfaces/INotifyLeaderboardActivate.hpp"
#include "shared/Interfaces/INotifyLeaderboardChange.hpp"
#include "shared/Interfaces/INotifyLeaderboardSet.hpp"
#include "shared/Interfaces/INotifyLeaderboardLoad.hpp"
using namespace LeaderboardCore;
using namespace LeaderboardCore::Interfaces;

#include <vector>

#define NeededInterfaces                                                                                                                                                                                                                           \
{                                                                                                                                                                                                                                            \
    classof(INotifyLeaderboardSet*), classof(INotifyLeaderboardActivate*), classof(INotifyLeaderboardLoad*), classof(INotifyLeaderboardChange*) \
}

___DECLARE_TYPE_WRAPPER_INHERITANCE(LeaderboardCore::UI::ViewControllers, LeaderboardNavigationButtonsController, Il2CppTypeEnum::IL2CPP_TYPE_CLASS, HMUI::ViewController, "LeaderboardCore.UI.ViewControllers", NeededInterfaces, 0, nullptr,
DECLARE_INSTANCE_METHOD(void, OnEnable);
    public:
        void OnLeaderboardActivated(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

        void OnLeaderboardLoaded(bool loaded);

        void OnLeaderboardChanged(const std::vector<Models::CustomLeaderboard>& customLeaderboards);

        void OnLeaderboardSet(IDifficultyBeatmap* diff);
    private:
        QuestUI::FloatingScreen* m_buttonsFloatingScreen;
        QuestUI::FloatingScreen* m_panelFloatingScreen;
        UnityEngine::Transform* m_containerTransform;
        Sombrero::FastVector3 m_containerPos;
        IPreviewBeatmapLevel* m_selectedLevel;
        std::vector<Models::CustomLeaderboard*> m_customLeaderboards;
        int m_currentIndex;
        Models::CustomLeaderboard* m_customLeaderboard;

        void YeetDefault();

        void UnYeetDefault();
)