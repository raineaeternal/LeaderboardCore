#pragma once

#include "questui/shared/CustomTypes/Components/FloatingScreen/FloatingScreen.hpp"
#include "custom-types/shared/macros.hpp"

#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "HMUI/ViewController.hpp"

#include "GlobalNamespace/IPreviewBeatmapLevel.hpp"
#include "GlobalNamespace/IDifficultyBeatmap.hpp"
#include "HMUI/ViewController.hpp"
#include "HMUI/ViewController_DidActivateDelegate.hpp"

#include "shared/Models/CustomLeaderboard.hpp"
#include "shared/Interfaces/INotifyLeaderboardActivate.hpp"
#include "shared/Interfaces/INotifyLeaderboardChange.hpp"
#include "shared/Interfaces/INotifyLeaderboardSet.hpp"
#include "shared/Interfaces/INotifyLeaderboardLoad.hpp"

#include <vector>

DECLARE_CLASS_CODEGEN(LeaderboardCore::UI::ViewControllers, LeaderboardNavigationButtonsController, HMUI::ViewController,
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button*, m_leftButton);
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button*, m_rightButton);
    DECLARE_INSTANCE_FIELD(QuestUI::FloatingScreen*, m_buttonsFloatingScreen);
    DECLARE_INSTANCE_FIELD(QuestUI::FloatingScreen*, m_customPanelFloatingScreen);
    DECLARE_INSTANCE_FIELD(UnityEngine::Transform*, m_containerTransform);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::IPreviewBeatmapLevel*, m_selectedLevel);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::PlatformLeaderboardViewController*, m_platformLeaderboardViewController);
    DECLARE_INSTANCE_FIELD(bool, m_leaderboardLoaded);
    DECLARE_INSTANCE_FIELD(UnityEngine::Vector3, m_containerPos);
    DECLARE_INSTANCE_FIELD(int, m_currentIndex);

    DECLARE_INSTANCE_FIELD(HMUI::ViewController::DidActivateDelegate*, platformLeaderboardViewController_didActivateEvent);

    DECLARE_INSTANCE_METHOD(bool, get_ShowDefaultLeaderboard);
    DECLARE_INSTANCE_METHOD(bool, get_leftButtonActive);
    DECLARE_INSTANCE_METHOD(bool, get_rightButtonActive);

    DECLARE_INSTANCE_METHOD(void, OnEnable);
    DECLARE_INSTANCE_METHOD(void, LeftButtonClick);
    DECLARE_INSTANCE_METHOD(void, RightButtonClick);
    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::ViewController::DidActivate>::get(), bool firstActivation, bool addedToHeirarchy, bool screenSystemDisabling);

    public:
        std::vector<LeaderboardCore::Interfaces::INotifyLeaderboardSet*> leaderboardSetList;
        std::vector<LeaderboardCore::Interfaces::INotifyLeaderboardChange*> leaderboardChangeList;
        std::vector<LeaderboardCore::Interfaces::INotifyLeaderboardLoad*> leaderboardLoadList;
        std::vector<LeaderboardCore::Interfaces::INotifyScoreSaberActive*> scoresaberActiveList;

        void OnScoreSaberActivated();

        void OnLeaderboardActivated(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

        void OnLeaderboardLoaded(bool loaded);

        void OnLeaderboardChanged(const std::vector<LeaderboardCore::Models::CustomLeaderboard*>& customLeaderboards);

        void OnLeaderboardSet(GlobalNamespace::IDifficultyBeatmap* diff);

        void AddLeaderboardSet(LeaderboardCore::Interfaces::INotifyLeaderboardSet* interface);

        // void AddScoreSaberActivated(LeaderboardCore::Interfaces::INotifyScoreSaberActive* interface);  // TODO: Uncomment if SS decides to not play nice

        void AddLeaderboardChange(LeaderboardCore::Interfaces::INotifyLeaderboardChange* interface);

        void AddLeaderboardLoad(LeaderboardCore::Interfaces::INotifyLeaderboardLoad* interface);
    private:
        std::vector<LeaderboardCore::Models::CustomLeaderboard*> m_customLeaderboards;
        LeaderboardCore::Models::CustomLeaderboard* m_lastLeaderboard;

        int get_leaderboardIndex();
        void SwitchToDefault();
        void SwitchToLastLeaderboard();

        void Dispose();
        void Initialize();
        void YeetDefault();
        void UnYeetDefault();
        void UpdateButtons();
)