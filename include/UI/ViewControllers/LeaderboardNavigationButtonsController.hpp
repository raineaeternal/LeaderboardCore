#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"

#include "HMUI/ViewController.hpp"
#include "Zenject/IInitializable.hpp"
#include "System/IDisposable.hpp"
#include "GlobalNamespace/PlatformLeaderboardViewController.hpp"
#include "GlobalNamespace/IPreviewBeatmapLevel.hpp"
#include "UnityEngine/UI/Button.hpp"

#include "bsml/shared/BSML/FloatingScreen/FloatingScreen.hpp"
#include "Models/CustomLeaderboard.hpp"

#include <set>
#include <unordered_map>

DECLARE_CLASS_CODEGEN_INTERFACES(LeaderboardCore::UI::ViewControllers, LeaderboardNavigationButtonsController, HMUI::ViewController, std::vector<Il2CppClass*>({classof(::Zenject::IInitializable*), classof(::System::IDisposable*)}),
    DECLARE_INSTANCE_FIELD_PRIVATE(GlobalNamespace::PlatformLeaderboardViewController*, _platformLeaderboardViewController);
    DECLARE_INSTANCE_FIELD_PRIVATE(BSML::FloatingScreen*, _buttonsFloatingScreen);
    DECLARE_INSTANCE_FIELD_PRIVATE(BSML::FloatingScreen*, _customPanelFloatingScreen);
    
    DECLARE_INSTANCE_FIELD_PRIVATE(UnityEngine::UI::Button*, _leftButton);
    DECLARE_INSTANCE_FIELD_PRIVATE(UnityEngine::UI::Button*, _rightButton);

    DECLARE_INSTANCE_FIELD_PRIVATE(UnityEngine::Transform*, _containerTransform);
    DECLARE_INSTANCE_FIELD_PRIVATE(UnityEngine::Vector3, _containerPosition);
    DECLARE_INSTANCE_FIELD_PRIVATE(bool, _leaderboardLoaded);
    DECLARE_INSTANCE_FIELD_PRIVATE(GlobalNamespace::IPreviewBeatmapLevel*, _selectedLevel);
    DECLARE_INSTANCE_FIELD_PRIVATE(int, _currentIndex);

    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::HMUI::ViewController::DidActivate>::get(), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
    DECLARE_OVERRIDE_METHOD(void, Initialize, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::Zenject::IInitializable::Initialize>::get());
    DECLARE_OVERRIDE_METHOD(void, Dispose, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::System::IDisposable::Dispose>::get());

    DECLARE_INJECT_METHOD(void, Inject, GlobalNamespace::PlatformLeaderboardViewController* platformLeaderboardViewController);

    DECLARE_INSTANCE_METHOD(void, OnEnable);
    DECLARE_INSTANCE_METHOD(void, LeftButtonClick);
    DECLARE_INSTANCE_METHOD(void, RightButtonClick);

    DECLARE_INSTANCE_METHOD(void, UpdateButtonsActive);
    DECLARE_INSTANCE_METHOD(bool, get_leftButtonActive);
    DECLARE_INSTANCE_METHOD(bool, get_rightButtonActive);
    DECLARE_INSTANCE_METHOD(bool, get_showDefaultLeaderboard);
    DECLARE_INSTANCE_METHOD(bool, get_levelIsCustom);
    public:
        void OnScoreSaberActivated();
        void OnLeaderboardSet(GlobalNamespace::IDifficultyBeatmap* difficultyBeatmap);
        void OnLeaderboardLoaded(bool loaded);

    private:
        void OnLeaderboardActivated(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
        void SwitchToDefault(::LeaderboardCore::Models::CustomLeaderboard* lastLeaderboard = nullptr);
        void SwitchToLastLeaderboard();
        void YeetDefault();
        void UnYeetDefault();
        void RightButtonClick_overload(::LeaderboardCore::Models::CustomLeaderboard* lastLeaderboard);
        void OnLeaderboardsChanged(const std::set<::LeaderboardCore::Models::CustomLeaderboard*>& orderedCustomLeaderboards, const std::unordered_map<std::string, ::LeaderboardCore::Models::CustomLeaderboard*>& customLeaderboardsById);
        std::set<::LeaderboardCore::Models::CustomLeaderboard*> orderedCustomLeaderboards;
        std::unordered_map<std::string, ::LeaderboardCore::Models::CustomLeaderboard*> customLeaderboardsById;
)