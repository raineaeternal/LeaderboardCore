#include "UI/LeaderboardNavigationController.hpp"

#include "logging.hpp"
#include "bsml/shared/BSML.hpp"
#include "assets.hpp"

DEFINE_TYPE(LeaderboardCore::UI, LeaderboardNavigationController);

namespace LeaderboardCore::UI {

    void LeaderboardNavigationController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
        DEBUG("LeaderboardNavigationController::DidActivate");
        if (firstActivation) {
            BSML::parse_and_construct(IncludedAssets::LeaderboardNavigationButtons_bsml, transform, this);
        }
        if (addedToHierarchy) {
            // SetChildViewControllers(ArrayW<HMUI::ViewController*>({customPlatformLeaderboardViewController, customPanelViewController}));
        }
    }
    
    void LeaderboardNavigationController::DidDeactivate(bool removedFromHierarchy, bool screenSystemDisabling) {
        if (removedFromHierarchy) {
            DEBUG("LeaderboardNavigationController::DidDeactivate");
            // ClearChildViewControllers();
        }
    }

    bool LeaderboardNavigationController::get_leftButtonActive() {
        // auto result = (_currentIndex > 0 && (get_showDefaultLeaderboard() || _currentIndex > 1 )) && _leaderboardLoaded && get_levelIsCustom();
        // DEBUG("get_leftButtonActive -> {}", result);
        return true;
    }

    bool LeaderboardNavigationController::get_rightButtonActive() {
        // auto result = _currentIndex < Managers::CustomLeaderboardManager::orderedCustomLeaderboards.size() && _leaderboardLoaded && get_levelIsCustom();
        // DEBUG("get_rightButtonActive -> {}", result);
        return true;
    }

}