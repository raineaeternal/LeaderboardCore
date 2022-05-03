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

#define NeededInterfaces                                                                                                                                                                                                                     \
{                                                                                                                                                                                                                                            \
    classof(INotifyLeaderboardSet*), classof(INotifyLeaderboardActivate*), classof(INotifyLeaderboardLoad*), classof(INotifyLeaderboardChange*)                                                                                              \
}

DECLARE_CLASS_CODEGEN(LeaderboardCore::UI::ViewControllers, LeaderboardNavigationButtonsController, HMUI::ViewController,
    DECLARE_INSTANCE_METHOD(void, OnEnable);
    public:
        std::vector<INotifyLeaderboardSet*> leaderboardSetList;
        std::vector<INotifyLeaderboardChange*> leaderboardChangeList;
        std::vector<INotifyLeaderboardLoad*> leaderboardLoadList;
        std::vector<INotifyScoreSaberActive*> scoresaberActiveList;

        void OnScoreSaberActivated();

        void OnLeaderboardActivated(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

        void OnLeaderboardLoaded(bool loaded);

        void OnLeaderboardChanged(const std::vector<Models::CustomLeaderboard*>& customLeaderboards);

        void OnLeaderboardSet(IDifficultyBeatmap* diff);

        void AddLeaderboardSet(INotifyLeaderboardSet* interface);

        void AddScoreSaberActivated(INotifyScoreSaberActive* interface);

        void AddLeaderboardChange(INotifyLeaderboardChange* interface);

        void AddLeaderboardLoad(INotifyLeaderboardLoad* interface);
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