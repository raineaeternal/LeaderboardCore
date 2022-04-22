#include "shared/Models/CustomLeaderboard.hpp"

namespace LeaderboardCore::Models {
    void CustomLeaderboard::Show(FloatingScreen* panelScreen, 
    FastVector3 leaderboardPos, 
    PlatformLeaderboardViewController* leaderboardViewController) {
        if (m_LeaderboardViewController != nullptr) {
            // panelScreen; // TODO: Bug myself (raine) to implement SetRootViewController into QUI. (or workaround temporarily, whatever comes first)
            if (!m_PanelViewController->get_isActiveAndEnabled()) {
                m_PanelViewController->get_gameObject()->set_active(true);
            }
        } else {
            // TODO: Funny SetRootViewController again :msnD:
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

    void CustomLeaderboard::Hide(FloatingScreen* panelScreen) {
        if (panelScreen != nullptr) {
            // TODO: SetRootViewController (or the temp. workaround)
        } else {
            m_PanelViewController->get_gameObject()->set_active(false);
        }

        if (m_LeaderboardViewController != nullptr) {
            m_LeaderboardViewController->__Deactivate(false, true, false);
        }
    }
}
