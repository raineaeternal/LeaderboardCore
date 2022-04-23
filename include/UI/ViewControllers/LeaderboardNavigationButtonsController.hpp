#pragma once

// #include "shared/Interfaces/INotifyLeaderboardActivate.hpp"
// #include "shared/Interfaces/INotifyLeaderboardChange.hpp"
// #include "shared/Interfaces/INotifyLeaderboardSet.hpp"
// #include "shared/Interfaces/INotifyScoreUpload.hpp"
// using namespace LeaderboardCore;

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
using namespace GlobalNamespace;

#include "Models/CustomLeaderboard.hpp"
using namespace LeaderboardCore;

#include <vector>

namespace LeaderboardCore::UI::ViewControllers {
    class LeaderboardNavigationButtonsController {
    public:
        void OnEnable();

        void OnLeaderboardActivated(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

        void OnLeaderboardLoaded(bool loaded);

        // void OnScoreSaberActivated(); /// TODO: Remove if ScoreSaber decides to play nice

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
    };
}
