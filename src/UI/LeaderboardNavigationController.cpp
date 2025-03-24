#include "UI/LeaderboardNavigationController.hpp"

#include "logging.hpp"

DEFINE_TYPE(LeaderboardCore::UI, LeaderboardNavigationController);

void LeaderboardCore::UI::LeaderboardNavigationController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    if (firstActivation) {
        DEBUG("LeaderboardNavigationController::DidActivate");
    }
}

void LeaderboardCore::UI::LeaderboardNavigationController::DidDeactivate(bool removedFromHierarchy, bool screenSystemDisabling) {
    if (removedFromHierarchy) {
        DEBUG("LeaderboardNavigationController::DidDeactivate");
    }
}
