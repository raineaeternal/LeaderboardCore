#pragma once

#include <vector>
#include "shared/Interfaces/INotifyLeaderboardChange.hpp"
#include "shared/Models/CustomLeaderboard.hpp"
using namespace LeaderboardCore::Models;
using namespace LeaderboardCore::Interfaces;

namespace LeaderboardCore {
    class CustomLeaderboardManager {
    private:
        std::vector<INotifyLeaderboardChange*> m_notifyCustomLeaderboardChanges;
        std::vector<Models::CustomLeaderboard*> m_customLeaderboards;

        void OnLeaderboardChange();
    public:
        void Register(CustomLeaderboard* customLeaderboard);
        void Unregister(CustomLeaderboard* customLeaderboard);
    };
}
