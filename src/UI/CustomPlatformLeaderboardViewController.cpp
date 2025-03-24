#include "UI/CustomPlatformLeaderboardViewController.hpp"

#include "UI/LeaderboardNavigationController.hpp"
#include "logging.hpp"
#include "GlobalNamespace/PlatformLeaderboardViewController.hpp"
#include "GlobalNamespace/LevelStatsView.hpp"
#include "UnityEngine/Transform.hpp"
#include "GlobalNamespace/PlayerDataModel.hpp"

#include "bsml/shared/BSML-Lite/Creation/Text.hpp"

DEFINE_TYPE(LeaderboardCore::UI, CustomPlatformLeaderboardViewController);

using namespace GlobalNamespace;

namespace LeaderboardCore::UI {

    void CustomPlatformLeaderboardViewController::Initialise() {
        DEBUG("LeaderboardNavigationController::Initialise");
        
        platformLeaderboardViewController = soloFreePlayFlowCoordinator->_platformLeaderboardViewController;
        // this is so unbelieably illegal but bare with me lmao
        soloFreePlayFlowCoordinator->_platformLeaderboardViewController = reinterpret_cast<PlatformLeaderboardViewController*>(this);
    }

    void CustomPlatformLeaderboardViewController::Inject(LeaderboardNavigationController* nav, SoloFreePlayFlowCoordinator* solo) {
        leaderboardNavigationController = nav;
        soloFreePlayFlowCoordinator = solo;
    }

    void CustomPlatformLeaderboardViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
        DEBUG("CustomPlatformLeaderboardViewController::DidActivate");
        if (firstActivation) {
            BSML::Lite::CreateText(transform, "knob", UnityEngine::Vector2{0, 0}, {60, 7});
            leaderboardNavigationController->__Init(screen, this, nullptr);
            transform->position = platformLeaderboardViewController->transform->position;
            transform->localScale = platformLeaderboardViewController->transform->localScale;
            rectTransform->sizeDelta = platformLeaderboardViewController->rectTransform->sizeDelta;
            platformLeaderboardViewController->_levelStatsView->transform->SetParent(transform, false);
        }
        gameObject->set_active(true);
        leaderboardNavigationController->__Activate(false, false);
    }
    
    void CustomPlatformLeaderboardViewController::DidDeactivate(bool removedFromHierarchy, bool screenSystemDisabling) {
        DEBUG("CustomPlatformLeaderboardViewController::DidDeactivate");
        leaderboardNavigationController->__Deactivate(false, true, false);
    }

    void CustomPlatformLeaderboardViewController::SetData(ByRef<BeatmapKey> beatmapKey) {
        DEBUG("selected level {}", beatmapKey->levelId);
        currentBeatmap = *reinterpret_cast<BeatmapKey*>(beatmapKey.convert());
        RefreshLevelStats();
    }

    void CustomPlatformLeaderboardViewController::RefreshLevelStats() {
        DEBUG("CustomPlatformLeaderboardViewController::RefreshLevelStats");
        DEBUG("is parent: {}", platformLeaderboardViewController->_levelStatsView->transform->parent == platformLeaderboardViewController->transform);
        platformLeaderboardViewController->_levelStatsView->ShowStats(ByRef<BeatmapKey>(currentBeatmap), platformLeaderboardViewController->_playerDataModel->playerData);
    }

    void CustomPlatformLeaderboardViewController::Dispose() {
        DEBUG("CustomPlatformLeaderboardViewController::Dispose");
    }
}
