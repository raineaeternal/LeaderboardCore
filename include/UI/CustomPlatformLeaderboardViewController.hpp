#pragma once

#include "custom-types/shared/macros.hpp"
#include "HMUI/ViewController.hpp"
#include "GlobalNamespace/LeaderboardViewController.hpp"
#include "Zenject/IInitializable.hpp"
#include "System/IDisposable.hpp"
#include "GlobalNamespace/SoloFreePlayFlowCoordinator.hpp"
#include "UI/LeaderboardNavigationController.hpp"
#include "lapiz/shared/macros.hpp"

DECLARE_CLASS_CODEGEN_INTERFACES(LeaderboardCore::UI, CustomPlatformLeaderboardViewController, GlobalNamespace::LeaderboardViewController, Zenject::IInitializable*, System::IDisposable*) {
    DECLARE_INJECT_METHOD(void, Inject, LeaderboardNavigationController* nav, GlobalNamespace::SoloFreePlayFlowCoordinator* solo);
    
    DECLARE_OVERRIDE_METHOD_MATCH(void, DidActivate, &HMUI::ViewController::DidActivate, bool, bool, bool);
    DECLARE_OVERRIDE_METHOD_MATCH(void, DidDeactivate, &HMUI::ViewController::DidDeactivate, bool, bool);

    DECLARE_OVERRIDE_METHOD_MATCH(void, SetData, &GlobalNamespace::LeaderboardViewController::SetData, ByRef<GlobalNamespace::BeatmapKey> beatmapKey);
    DECLARE_OVERRIDE_METHOD_MATCH(void, RefreshLevelStats, &GlobalNamespace::LeaderboardViewController::RefreshLevelStats);

    DECLARE_OVERRIDE_METHOD_MATCH(void, Initialize, &Zenject::IInitializable::Initialize);
    DECLARE_OVERRIDE_METHOD_MATCH(void, Dispose, &System::IDisposable::Dispose);

    DECLARE_INSTANCE_METHOD(void, PostParse);

    DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, noLeaderboard);
    DECLARE_INSTANCE_FIELD(LeaderboardNavigationController*, leaderboardNavigationController);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::SoloFreePlayFlowCoordinator*, soloFreePlayFlowCoordinator);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::PlatformLeaderboardViewController*, platformLeaderboardViewController);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::BeatmapKey, currentBeatmap);
};
