#include "UI/PlatformLeaderboardViewController.hpp"

#include "logging.hpp"
DEFINE_TYPE(LeaderboardCore::UI, CustomPlatformLeaderboardViewController);

void LeaderboardCore::UI::CustomPlatformLeaderboardViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    if (firstActivation) {
        DEBUG("PlatformLeaderboardViewController::DidActivate");
    }
}

void LeaderboardCore::UI::CustomPlatformLeaderboardViewController::DidDeactivate(bool removedFromHierarchy, bool screenSystemDisabling) {
    if (removedFromHierarchy) {
        DEBUG("PlatformLeaderboardViewController::DidDeactivate");
    }
}
