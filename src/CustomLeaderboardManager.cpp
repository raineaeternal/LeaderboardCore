#include "shared/CustomLeaderboardManager.hpp"
#include "shared/Models/CustomLeaderboard.hpp"

namespace LeaderboardCore {
    CustomLeaderboardManager::m_notifyCustomLeaderboardChanges;
    CustomLeaderboardManager::m_customLeaderboards;

    CustomLeaderboardManager::Register(CustomLeaderboard* customLeaderboard) {
        if (!customLeaderboards->Contains(m_customLeaderboards)) {
            m_customLeaderboards.push_back(customLeaderboard);
            OnLeaderboardChange();
        }
    }

    CustomLeaderboardManager::Unregister(CustomLeaderboard* customLeaderboard) {
        m_customLeaderboards.pop_back(customLeaderboard);
        OnLeaderboardChange();
    }

    CustomLeaderboardManager::OnLeaderboardChange() {
        for (auto& notifiedLeaderboard : CustomLeaderboardManager::m_notifyCustomLeaderboardChanges) {
            notifiedLeaderboard->OnLeaderboardsChanged(m_customLeaderboards)
        }
    }
}