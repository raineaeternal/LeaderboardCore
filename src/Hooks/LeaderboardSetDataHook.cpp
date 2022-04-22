#include "main.hpp"
#include "include/Hooks/LeaderboardHook.hpp"

#include "GlobalNamespace/PlatformLeaderboardViewController.hpp"
#include "GlobalNamespace/IDifficultyBeatmap.hpp"
using namespace GlobalNamespace;

#include "shared/Interfaces/INotifyLeaderboardSet.hpp"
using namespace LeaderboardCore::Interfaces;

#include <vector>


MAKE_HOOK_MATCH(m_LeaderboardData_SetData, 
    &PlatformLeaderboardViewController::SetData, 
    void, 
    PlatformLeaderboardViewController* self,
    IDifficultyBeatmap* diff) {
    m_LeaderboardData_SetData(self, diff);

    std::vector<INotifyLeaderboardSet*> m_notifyLeaderboardSets;
    for (auto& leaderboard : m_notifyLeaderboardSets) {
        leaderboard->OnLeaderboardSet(diff);
    }
}

void InstallHook() {
    INSTALL_HOOK(getLogger(), m_LeaderboardData_SetData)
}
