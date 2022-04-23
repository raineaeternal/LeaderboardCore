#include "shared/CustomLeaderboardManager.hpp"
#include "shared/Models/CustomLeaderboard.hpp"
#include <vector>

namespace LeaderboardCore {
    void CustomLeaderboardManager::Register(CustomLeaderboard* customLeaderboard) {
        auto itr = std::find(m_customLeaderboards.begin(), m_customLeaderboards.end(), customLeaderboard);
        if (itr == m_customLeaderboards.end()) {
            m_customLeaderboards.emplace_back(customLeaderboard);
            OnLeaderboardChange();
        }
    }

    void CustomLeaderboardManager::Unregister(CustomLeaderboard* customLeaderboard) {
        auto itr = std::find(m_customLeaderboards.begin(), m_customLeaderboards.end(), customLeaderboard);
        m_customLeaderboards.erase(itr, itr++);
        OnLeaderboardChange();
    }

    void CustomLeaderboardManager::OnLeaderboardChange() {
        for (auto& notifiedLeaderboard : CustomLeaderboardManager::m_notifyCustomLeaderboardChanges) {
            notifiedLeaderboard->OnLeaderboardChange(m_customLeaderboards);
        }
    }
}