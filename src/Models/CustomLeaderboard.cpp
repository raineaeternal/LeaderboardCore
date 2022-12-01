#include "Models/CustomLeaderboard.hpp"
#include "GlobalNamespace/SharedCoroutineStarter.hpp"
#include "HMUI/ViewController.hpp"
#include "HMUI/ViewController_AnimationType.hpp"

#include "logger.h"

namespace LeaderboardCore::Models {
    void CustomLeaderboard::Show(BSML::FloatingScreen* panelScreen, UnityEngine::Vector3 leaderboardPosition, GlobalNamespace::PlatformLeaderboardViewController* platformLeaderboardViewController) {
        panelScreen->get_gameObject()->SetActive(true);

        if (!panelScreen->get_isActiveAndEnabled()) {
            GlobalNamespace::SharedCoroutineStarter::get_instance()->
                StartCoroutine(custom_types::Helpers::CoroutineHelper::New(
                    CustomLeaderboard::WaitForScreen(panelScreen, leaderboardPosition, platformLeaderboardViewController))
                );
            return;
        }
        auto panelViewController = get_panelViewController();
        if (panelViewController && panelViewController->m_CachedPtr.m_value) {
            panelScreen->SetRootViewController(panelViewController, HMUI::ViewController::AnimationType::None);

            if (!panelViewController->get_isActiveAndEnabled()) {
                DEBUG("setting panelview GO active!");
                panelViewController->get_gameObject()->SetActive(true);
        } 
        } else {
            DEBUG("Setting panelview root viewcontroller to null!");
            panelScreen->SetRootViewController(nullptr, HMUI::ViewController::AnimationType::None);
        }

        auto leaderboardViewController = get_leaderboardViewController();
        if (leaderboardViewController && leaderboardViewController->m_CachedPtr.m_value) {
            leaderboardViewController->get_transform()->set_localPosition(leaderboardPosition);

            if (leaderboardViewController->get_screen() == nullptr) {
                DEBUG("Initializing platformleaderboardviewcontroller!");
                leaderboardViewController->__Init(platformLeaderboardViewController->screen, platformLeaderboardViewController, nullptr);
            }

            leaderboardViewController->__Activate(false, false);
            leaderboardViewController->get_transform()->SetParent(platformLeaderboardViewController->get_transform());
        }
    }

    void CustomLeaderboard::Hide(BSML::FloatingScreen* panelScreen) {
        if (panelScreen && panelScreen->m_CachedPtr.m_value) {
            if (panelScreen->get_isActiveAndEnabled()) {
                DEBUG("Setting root viewcontroller to null!");
                panelScreen->SetRootViewController(nullptr, HMUI::ViewController::AnimationType::None);
            } else {
                DEBUG("setting GO to nonactive!");
                auto panelViewController = get_panelViewController();
                if (panelViewController && panelViewController->m_CachedPtr.m_value) {
                    panelViewController->get_gameObject()->SetActive(false);
                }
            }
        }
    }

    custom_types::Helpers::Coroutine CustomLeaderboard::WaitForScreen(BSML::FloatingScreen* panelScreen, UnityEngine::Vector3 leaderboardPosition, GlobalNamespace::PlatformLeaderboardViewController* platformLeaderboardViewController) {
        while (!panelScreen->get_isActiveAndEnabled()) {
            DEBUG("Waiting for screen!");
            co_yield nullptr;
        }
        Show(panelScreen, leaderboardPosition, platformLeaderboardViewController);
        DEBUG("Screen shown!");
        co_return;
    }
}