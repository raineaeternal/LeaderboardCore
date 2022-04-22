#include "main.hpp"

#include "GlobalNamespace/PlatformLeaderboardViewController.hpp"
#include "GlobalNamespace/IDifficultyBeatmap.hpp"

void 


MAKE_HOOK_MATCH(m_LeaderboardData_SetData, 
    &PlatformLeaderboardViewController, 
    void, 
    PlatformLeaderboardViewController::SetData*, 
    self) {
    m_LeaderboardData_SetData(self) 
}
