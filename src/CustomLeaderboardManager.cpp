#include "shared/CustomLeaderboardManager.hpp"
#include "shared/Models/CustomLeaderboard.hpp"
#include <vector>
#include <find>

namespace LeaderboardCore {
    std::vector<INotifyLeaderboardChange*> CustomLeaderboardManager::m_notifyCustomLeaderboardChanges;
    std::vector<CustomLeaderboard*> CustomLeaderboardManager::m_customLeaderboards;

    CustomLeaderboardManager::Register(CustomLeaderboard* customLeaderboard) {
        auto itr = std::find(m_customLeaderboards.begin(), m_customLeaderboards.end(), customLeaderboard);
        if (itr == m_customLeaderboards.end()) {
            m_customLeaderboards.emplace_back(customLeaderboard);
            OnLeaderboardChange();
        }
    }

    CustomLeaderboardManager::Unregister(CustomLeaderboard* customLeaderboard) {
        auto itr = std::find(m_customLeaderboards.begin(), m_customLeaderboards.end(), customLeaderboard);
        m_customLeaderboards.erase(itr, itr++);
        OnLeaderboardChange();
    }

    CustomLeaderboardManager::OnLeaderboardChange() {
        for (auto& notifiedLeaderboard : CustomLeaderboardManager::m_notifyCustomLeaderboardChanges) {
            notifiedLeaderboard->OnLeaderboardsChanged(m_customLeaderboards)
        }
    }
}