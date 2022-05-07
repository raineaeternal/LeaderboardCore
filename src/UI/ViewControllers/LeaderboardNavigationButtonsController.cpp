#include "include/UI/ViewControllers/LeaderboardNavigationButtonsController.hpp"

#include "GlobalNamespace/IDifficultyBeatmap.hpp"

DEFINE_TYPE(LeaderboardCore::UI::ViewControllers, LeaderboardNavigationButtonsController)

namespace LeaderboardCore::UI::ViewControllers {
    void LeaderboardNavigationButtonsController::OnEnable() {

    }

    void LeaderboardNavigationButtonsController::AddLeaderboardSet(INotifyLeaderboardSet *interface) {
        leaderboardSetList.push_back(interface);
    }
    
    void LeaderboardNavigationButtonsController::AddLeaderboardChange(INotifyLeaderboardChange *interface) {
        leaderboardChangeList.push_back(interface);
    }

    void LeaderboardNavigationButtonsController::AddLeaderboardLoad(INotifyLeaderboardLoad *interface) {
        leaderboardLoadList.push_back(interface);
    }

    // TODO: Uncomment if SS decides to not play nice.
    // void LeaderboardNavigationButtonsController::AddScoreSaberActivated(INotifyScoreSaberActive *interface) {
    //     scoresaberActiveList.push_back(interface);
    // }

    void LeaderboardNavigationButtonsController::OnScoreSaberActivated() {
        for(auto interface : scoresaberActiveList) {
            interface->OnScoreSaberActivated();
        }
    }

    void LeaderboardNavigationButtonsController::OnLeaderboardActivated(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {

    }

    void LeaderboardNavigationButtonsController::OnLeaderboardChanged(const std::vector<Models::CustomLeaderboard*>& customLeaderboards) {
        for(auto instance : leaderboardChangeList) {
            instance->OnLeaderboardChange(customLeaderboards);
        }
    }

    void LeaderboardNavigationButtonsController::OnLeaderboardLoaded(bool loaded) {
        for(auto interface : leaderboardLoadList) {
            interface->OnLeaderboardLoaded(loaded);
        }
    }
    
    void LeaderboardNavigationButtonsController::OnLeaderboardSet(IDifficultyBeatmap* diff) {
        for(auto interface : leaderboardSetList) {
            interface->OnLeaderboardSet(diff);
        }
    }

    void LeaderboardNavigationButtonsController::YeetDefault() {

    }

    void LeaderboardNavigationButtonsController::UnYeetDefault() {

    }
}