#include "shared/Models/CustomLeaderboard.hpp"

namespace LeaderboardCore::Models {
    void CustomLeaderboard::Show(HMUI::Screen* panelScreen, 
    UnityEngine::Vector3 leaderboardPos, 
    PlatformLeaderboardViewController* leaderboardViewController) {
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

    void CustomLeaderboard::Hide(HMUI::Screen* panelScreen) {
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
