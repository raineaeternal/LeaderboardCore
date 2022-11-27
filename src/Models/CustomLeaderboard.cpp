#include "Models/CustomLeaderboard.hpp"
#include "HMUI/ViewController.hpp"
#include "HMUI/ViewController_AnimationType.hpp"

namespace LeaderboardCore::Models {
    void CustomLeaderboard::Show(BSML::FloatingScreen* panelScreen, UnityEngine::Vector3 leaderboardPosition, GlobalNamespace::PlatformLeaderboardViewController* platformLeaderboardViewController) {
        panelScreen->get_gameObject()->SetActive(true);

        if (!panelScreen->get_isActiveAndEnabled()) {
            custom_types::Helpers::CoroutineHelper::New(CustomLeaderboard::WaitForScreen(panelScreen, leaderboardPosition, platformLeaderboardViewController));
            return;
        }

        if (get_panelViewController() != nullptr) {
            panelScreen->SetRootViewController(get_panelViewController(), HMUI::ViewController::AnimationType::None);

            if (!get_panelViewController()->get_isActiveAndEnabled()) {
                get_panelViewController()->get_gameObject()->SetActive(true);
            } else {
                panelScreen->SetRootViewController(nullptr, HMUI::ViewController::AnimationType::None);
            }
        }

        if (get_leaderboardViewController() != nullptr) {
            get_leaderboardViewController()->get_transform()->get_localPosition() = leaderboardPosition;

            if (get_leaderboardViewController()->get_screen() == nullptr) {
                get_leaderboardViewController()->__Init(platformLeaderboardViewController->screen, platformLeaderboardViewController, nullptr);
            }

            get_leaderboardViewController()->__Activate(false, false);
            get_leaderboardViewController()->get_transform()->SetParent(platformLeaderboardViewController->get_transform());
        }
    }

    void CustomLeaderboard::Hide(BSML::FloatingScreen* panelScreen) {
        if (panelScreen != nullptr) {
            if (panelScreen->get_isActiveAndEnabled()) {
                panelScreen->SetRootViewController(nullptr, HMUI::ViewController::AnimationType::None);
            } else {
                panelScreen->get_gameObject()->SetActive(false);
            }
        }
    }

    custom_types::Helpers::Coroutine CustomLeaderboard::WaitForScreen(BSML::FloatingScreen* panelScreen, UnityEngine::Vector3 leaderboardPosition, GlobalNamespace::PlatformLeaderboardViewController* platformLeaderboardViewController) {
        while (!panelScreen->get_isActiveAndEnabled()) {
            return co_yield nullptr;
        }
        Show(panelScreen, leaderboardPosition, platformLeaderboardViewController);
    }
}