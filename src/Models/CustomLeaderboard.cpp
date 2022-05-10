#include "shared/Models/CustomLeaderboard.hpp"

namespace LeaderboardCore::Models {

    custom_types::Helpers::Coroutine CustomLeaderboard::WaitForScreen(QuestUI::FloatingScreen* panelScreen, UnityEngine::Vector3 leaderboardPosition, GlobalNamespace::PlatformLeaderboardViewController* platformLeaderboardViewController) {
        while(!panelScreen->get_isActiveAndEnabled()) {
            co_yield nullptr;
        }
        Show(panelScreen, leaderboardPosition, platformLeaderboardViewController);
        co_return;
    }
    
    void CustomLeaderboard::Show(QuestUI::FloatingScreen* panelScreen,
    UnityEngine::Vector3 leaderboardPos, 
    PlatformLeaderboardViewController* leaderboardViewController) {

        if (!panelScreen->get_isActiveAndEnabled()) {
            SharedCoroutineStarter::get_instance()
            ->StartCoroutine(custom_types::Helpers::CoroutineHelper::New(WaitForScreen(panelScreen, leaderboardPos, leaderboardViewController)));
        }

        if (panelScreen != nullptr) {
            panelScreen->SetRootViewController(m_PanelViewController, ViewController::AnimationType::None);

            if (!m_PanelViewController->get_isActiveAndEnabled()) {
                m_PanelViewController->get_gameObject()->set_active(true);
            }
        } else {
            panelScreen->SetRootViewController(nullptr, ViewController::AnimationType::None);
        }

        if (m_LeaderboardViewController != nullptr) {
            m_LeaderboardViewController->get_transform()->set_localPosition(leaderboardPos);

            if (m_LeaderboardViewController == nullptr) {
                m_LeaderboardViewController->__Init(leaderboardViewController->HMUI::ViewController::get_screen(), leaderboardViewController, nullptr);
            }
        }
        m_LeaderboardViewController->__Activate(false, false);
        m_LeaderboardViewController->get_transform()->set_parent(leaderboardViewController->get_transform());
    }

    void CustomLeaderboard::Hide(QuestUI::FloatingScreen* panelScreen) {
        if (panelScreen != nullptr) {
            panelScreen->SetRootViewController(nullptr, ViewController::AnimationType::None);
        } else {
            m_PanelViewController->get_gameObject()->set_active(false);
        }

        if (m_LeaderboardViewController != nullptr) {
            m_LeaderboardViewController->__Deactivate(false, true, false);
        }
    }
}
