#include "shared/Models/CustomLeaderboard.hpp"

namespace LeaderboardCore::Models {
    class CustomLeaderboard {
    public:
        HMUI::ViewController* m_PanelViewController;
        HMUI::ViewController* m_LeaderboardViewController; /// 
    private:
        void Show(FloatingScreen* panelScreen, 
        FastVector3 leaderboardPos, 
        PlatformLeaderboardViewController* leaderboardViewController) {
            if (m_PanelViewController != nullptr) {
                panelScreen; // TODO: Bug myself (raine) to implement SetRootViewController into QUI. (or workaround temporarily, whatever comes first)
                if (!m_PanelViewController->get_isActiveAndEnabled) {
                    m_PanelViewController->get_gameObject;
                    m_PanelViewController->set_enabled(true);
                }
            } else {
                
            }

            if () {

            }
            m_LeaderboardViewController->__Activate(false, false);
            m_LeaderboardViewController->get_transform;
        }

        void Hide(FloatingScreen panelScreen) {
            if (panelScreen != nullptr) {
                // TODO: SetRootViewController (or the temp. workaround)
            } else {

            }

            if () {

            }
        }
    };
}