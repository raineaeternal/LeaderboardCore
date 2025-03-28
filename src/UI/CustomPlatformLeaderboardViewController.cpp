#include "UI/CustomPlatformLeaderboardViewController.hpp"

#include "UI/LeaderboardNavigationController.hpp"
#include "logging.hpp"
#include "GlobalNamespace/PlatformLeaderboardViewController.hpp"
#include "GlobalNamespace/LevelStatsView.hpp"
#include "UnityEngine/Transform.hpp"
#include "GlobalNamespace/PlayerDataModel.hpp"
#include "UnityEngine/Vector3.hpp"
#include "bsml/shared/BSML.hpp"
#include "assets.hpp"

DEFINE_TYPE(LeaderboardCore::UI, CustomPlatformLeaderboardViewController);

using namespace GlobalNamespace;

namespace LeaderboardCore::UI {

    void CustomPlatformLeaderboardViewController::Initialise() {
        DEBUG("CustomPlatformLeaderboardViewController::Initialise");
        
        platformLeaderboardViewController = soloFreePlayFlowCoordinator->_platformLeaderboardViewController;
        platformLeaderboardViewController->_levelStatsView->transform->SetParent(transform, false);
        leaderboardNavigationController->transform->SetParent(transform, false);
        leaderboardNavigationController->transform->localPosition = {0.0f, 22.0f, 0.0f};
        // this is so unbelieably illegal but bare with me lmao
        soloFreePlayFlowCoordinator->_platformLeaderboardViewController = reinterpret_cast<PlatformLeaderboardViewController*>(this);
    }

    void CustomPlatformLeaderboardViewController::Inject(LeaderboardNavigationController* nav, SoloFreePlayFlowCoordinator* solo) {
        leaderboardNavigationController = nav;
        soloFreePlayFlowCoordinator = solo;
    }

    void CustomPlatformLeaderboardViewController::PostParse() {
        noLeaderboard->transform->localPosition = {0.0f, -5.5f, 0.0f};
    }

    void CustomPlatformLeaderboardViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
        DEBUG("CustomPlatformLeaderboardViewController::DidActivate");
        if (firstActivation) {
            BSML::parse_and_construct(IncludedAssets::PlaceholderLeaderboard_bsml, transform, this);
        }
        leaderboardNavigationController->__Init(screen, this, nullptr);
        leaderboardNavigationController->__Activate(true, false);
    }
    
    void CustomPlatformLeaderboardViewController::DidDeactivate(bool removedFromHierarchy, bool screenSystemDisabling) {
        DEBUG("CustomPlatformLeaderboardViewController::DidDeactivate");
        leaderboardNavigationController->__Deactivate(true, true, false);
    }

    void CustomPlatformLeaderboardViewController::SetData(ByRef<BeatmapKey> beatmapKey) {
        DEBUG("selected level {}", beatmapKey->levelId);
        currentBeatmap = *beatmapKey;
        RefreshLevelStats();
    }

    void CustomPlatformLeaderboardViewController::RefreshLevelStats() {
        DEBUG("CustomPlatformLeaderboardViewController::RefreshLevelStats");
        platformLeaderboardViewController->_levelStatsView->ShowStats(ByRef<BeatmapKey>(currentBeatmap), platformLeaderboardViewController->_playerDataModel->playerData);
    }

    void CustomPlatformLeaderboardViewController::Dispose() {
        DEBUG("CustomPlatformLeaderboardViewController::Dispose");
    }
}
