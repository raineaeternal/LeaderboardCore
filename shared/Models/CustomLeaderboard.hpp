#pragma once

#include "HMUI/ViewController.hpp"
#include "GlobalNamespace/PlatformLeaderboardViewController.hpp"
#include "UnityEngine/Vector3.hpp"

#include "custom-types/shared/coroutine.hpp"
#include "bsml/shared/BSML/FloatingScreen/FloatingScreen.hpp"
#include <string>

namespace LeaderboardCore {
    class CustomLeaderboardManager;
    namespace Models {
        class CustomLeaderboard {
            friend ::LeaderboardCore::CustomLeaderboardManager;
            public:
            protected:
                /// @brief getter for the panel view controller (the one above the leaderboard), you have to override this method!
                /// @return the view controller that belongs to the panel
                virtual HMUI::ViewController* get_panelViewController() = 0;
                /// @brief getter for the leaderboard view controller, you have to override this method!
                /// @return the view controller on which you display your scores
                virtual HMUI::ViewController* get_leaderboardViewController() = 0;
                /// @brief getter for the leaderboard ID, for if your mod has multiple ids
                /// @return string leaderboard id
                virtual std::string get_leaderboardId() { return ""; }
            private:
                /// @brief getter for the actual, to-be-used id, plugin id + leaderboard id
                /// @return leaderboard ID string
                std::string get_LeaderboardId() { return pluginId + get_leaderboardId(); }
                std::string pluginId;
                /// @brief Shows the current leaderboard, internally used
                /// @param panelScreen the floating screen for the panel
                /// @param leaderboardPosition the position of the leaderboard
                /// @param platformLeaderboardViewController the existing leaderboard view from the game
                void Show(BSML::FloatingScreen* panelScreen, UnityEngine::Vector3 leaderboardPosition, GlobalNamespace::PlatformLeaderboardViewController* platformLeaderboardViewController);
                /// @brief Hide this leaderboard, internally used
                /// @param panelScreen the floating screen for the panel
                void Hide(BSML::FloatingScreen* panelScreen);
                /// @brief coroutine used to wait for the screen to be done
                /// @param panelScreen the floating screen for the panel
                /// @param leaderboardPosition the position of it
                /// @param platformLeaderboardViewController the existing leaderboard view from the game
                custom_types::Helpers::Coroutine WaitForScreen(BSML::FloatingScreen* panelScreen, UnityEngine::Vector3 leaderboardPosition, GlobalNamespace::PlatformLeaderboardViewController* platformLeaderboardViewController);
        };
    }
}