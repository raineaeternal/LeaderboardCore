#pragma once

#include "GlobalNamespace/PlatformLeaderboardViewController.hpp"

namespace LeaderboardCore::Hooks {
    class LeaderboardPrefixFields {
    public:
        static GlobalNamespace::PlatformLeaderboardViewController* platformLeaderboardViewController;
    };
}