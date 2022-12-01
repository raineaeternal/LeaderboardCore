#pragma once

#include "GlobalNamespace/PlatformLeaderboardViewController.hpp"

namespace LeaderboardCore::Hooks {
    class LeaderboardPrefixFields {
    public:
        static GlobalNamespace::PlatformLeaderboardViewController* platformLeaderboardViewController;
    };
    class PlatformLeaderboardViewControllerEvents {
        public:
            static UnorderedEventCallback<bool, bool, bool> didActivateEvent;
    };
}