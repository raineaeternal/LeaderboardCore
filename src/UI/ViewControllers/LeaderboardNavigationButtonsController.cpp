#include "include/UI/ViewControllers/LeaderboardNavigationButtonsController.hpp"

#include "GlobalNamespace/IDifficultyBeatmap.hpp"
#include "GlobalNamespace/IBeatmapLevel.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "bsml/shared/BSML.hpp"
#include "assets.hpp"

DEFINE_TYPE(LeaderboardCore::UI::ViewControllers, LeaderboardNavigationButtonsController)

using namespace LeaderboardCore;
using namespace LeaderboardCore::Models;
using namespace LeaderboardCore::Interfaces;

namespace LeaderboardCore::UI::ViewControllers {
    void LeaderboardNavigationButtonsController::Initialize() {
        m_buttonsFloatingScreen = QuestUI::BeatSaberUI::CreateFloatingScreen({120.0f, 25.0f}, {0, 0, 0}, {0, 0, 0}, 0.0f, false, false)->GetComponent<QuestUI::FloatingScreen*>();
        
        auto btnScreenTransform = m_buttonsFloatingScreen->get_transform();
        btnScreenTransform->SetParent(m_platformLeaderboardViewController->get_rectTransform(), false);
        btnScreenTransform->set_localPosition({3, 50, 0});
        btnScreenTransform->set_localScale({1, 1, 1});

        auto btnScreenGo = m_buttonsFloatingScreen->get_gameObject();
        btnScreenGo->SetActive(false);
        btnScreenGo->SetActive(true);
        btnScreenGo->set_name("LeaderboardNavigationButtonsPanel");
        
        m_customPanelFloatingScreen = QuestUI::BeatSaberUI::CreateFloatingScreen({120.0f, 25.0f}, {0, 0, 0}, {0, 0, 0}, 0.0f, false, false)->GetComponent<QuestUI::FloatingScreen*>();
        
        auto customScreenTransform = m_customPanelFloatingScreen->get_transform();
        customScreenTransform->SetParent(m_platformLeaderboardViewController->get_rectTransform(), false);
        customScreenTransform->set_localPosition({3, 50, 0});
        customScreenTransform->set_localScale({1, 1, 1});

        auto customScreenGo = m_customPanelFloatingScreen->get_gameObject();
        customScreenGo->SetActive(false);
        customScreenGo->SetActive(true);
        customScreenGo->set_name("CustomLeaderboardPanel");

        platformLeaderboardViewController_didActivateEvent = BSML::MakeDelegate<HMUI::ViewController::DidActivateDelegate*>(
            std::function<void(bool, bool, bool)>(
                std::bind(&LeaderboardNavigationButtonsController::OnLeaderboardActivated, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
            )
        );
        m_platformLeaderboardViewController->add_didActivateEvent(platformLeaderboardViewController_didActivateEvent);
    }

    void LeaderboardNavigationButtonsController::Dispose() {
        if (m_buttonsFloatingScreen && m_buttonsFloatingScreen->m_CachedPtr.m_value) {
            UnityEngine::Object::DestroyImmediate(m_buttonsFloatingScreen->get_gameObject());
        }

        m_platformLeaderboardViewController->remove_didActivateEvent(platformLeaderboardViewController_didActivateEvent);
    }

    void LeaderboardNavigationButtonsController::DidActivate(bool firstActivation, bool addedToHeirarchy, bool screenSystemDisabling) {
        if (!firstActivation) return;
        BSML::parse_and_construct(IncludedAssets::LeaderboardNavigationButtons_bsml, get_transform(), this);
    }

    void LeaderboardNavigationButtonsController::OnEnable() {
        OnLeaderboardLoaded(m_leaderboardLoaded);
        if (!m_containerTransform || !m_containerTransform->m_CachedPtr.m_value) {
            m_containerTransform = m_platformLeaderboardViewController->get_transform()->Find("Container");
            m_containerPos = m_containerTransform->get_localPosition();
            OnLeaderboardLoaded(true);
        }
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
        for(auto& interface : scoresaberActiveList) {
            interface->OnScoreSaberActivated();
        }
    }

    void LeaderboardNavigationButtonsController::OnLeaderboardActivated(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
        m_platformLeaderboardViewController->remove_didActivateEvent(platformLeaderboardViewController_didActivateEvent);
        m_buttonsFloatingScreen->SetRootViewController(this, HMUI::ViewController::AnimationType::None);
    }

    void LeaderboardNavigationButtonsController::SwitchToDefault() {
        if (m_lastLeaderboard) m_lastLeaderboard->Hide(m_customPanelFloatingScreen);
        m_currentIndex = 0;
        UnYeetDefault();
    }

    void LeaderboardNavigationButtonsController::SwitchToLastLeaderboard() {
        if (m_lastLeaderboard) {
            int lastLeaderboardIndex = get_leaderboardIndex();
            m_lastLeaderboard->Show(m_customPanelFloatingScreen, m_containerPos, m_platformLeaderboardViewController);
            m_currentIndex = lastLeaderboardIndex + 1;
            YeetDefault();
        }
    }

    void LeaderboardNavigationButtonsController::OnLeaderboardChanged(const std::vector<Models::CustomLeaderboard*>& customLeaderboards) {
        m_customLeaderboards.clear();
        m_customLeaderboards.reserve(customLeaderboards.size());
        m_customLeaderboards.insert(m_customLeaderboards.begin(), customLeaderboards.begin(), customLeaderboards.end());
        
        int lastLeaderboardIndex = get_leaderboardIndex();
        if (m_lastLeaderboard && lastLeaderboardIndex == -1 && m_currentIndex != 0) {
            SwitchToDefault();
        } else if (m_lastLeaderboard && lastLeaderboardIndex != -1 && m_currentIndex == 0) {
            SwitchToLastLeaderboard();
        } else if (m_currentIndex == 0 && !get_ShowDefaultLeaderboard()) {
            RightButtonClick();
        }

        for(auto& instance : leaderboardChangeList) {
            instance->OnLeaderboardChange(customLeaderboards);
        }

        UpdateButtons();
    }

    void LeaderboardNavigationButtonsController::OnLeaderboardLoaded(bool loaded) {
        m_leaderboardLoaded = loaded;
        int lastLeaderboardIndex = get_leaderboardIndex();

        if (!il2cpp_utils::try_cast<GlobalNamespace::CustomPreviewBeatmapLevel>(m_selectedLevel).has_value()) {
            SwitchToDefault();
        } else {
            if (!loaded || (m_lastLeaderboard && lastLeaderboardIndex != -1 && m_currentIndex != 0)) {
                SwitchToDefault();
            } else if (m_lastLeaderboard && lastLeaderboardIndex != -1 && m_currentIndex == 0) {
                SwitchToLastLeaderboard();
            } else if (m_currentIndex == 0 && !get_ShowDefaultLeaderboard()) {
                RightButtonClick();
            }
        }

        for(auto& interface : leaderboardLoadList) {
            interface->OnLeaderboardLoaded(loaded);
        }

        UpdateButtons();
    }
    
    void LeaderboardNavigationButtonsController::OnLeaderboardSet(IDifficultyBeatmap* diff) {
        if (diff) {
            m_selectedLevel = diff->get_level() ? diff->get_level()->i_IPreviewBeatmapLevel() : nullptr;
        } else {
            m_selectedLevel = nullptr;
        }

        for(auto& interface : leaderboardSetList) {
            interface->OnLeaderboardSet(diff);
        }

        OnLeaderboardLoaded(m_leaderboardLoaded);
    }

    void LeaderboardNavigationButtonsController::YeetDefault() {
        if (m_containerTransform && m_containerTransform->m_CachedPtr.m_value) {
            m_containerTransform->set_localPosition({-999, -999, -999});
        }
    }

    void LeaderboardNavigationButtonsController::UnYeetDefault() {
        if (m_containerTransform && m_containerTransform->m_CachedPtr.m_value) {
            m_containerTransform->set_localPosition(m_containerPos);
        }
    }

    void LeaderboardNavigationButtonsController::LeftButtonClick() {
        if (!m_lastLeaderboard) return;

        m_lastLeaderboard->Hide(m_customPanelFloatingScreen);
        m_currentIndex--;

        if (m_currentIndex == 0) {
            UnYeetDefault();
            m_lastLeaderboard = nullptr;
        } else {
            m_lastLeaderboard = m_customLeaderboards.at(m_currentIndex - 1);
            m_lastLeaderboard->Show(m_customPanelFloatingScreen, m_containerPos, m_platformLeaderboardViewController);
        }

        UpdateButtons();
    }

    void LeaderboardNavigationButtonsController::RightButtonClick() {
        if (m_currentIndex == 0) YeetDefault();
        else if (m_lastLeaderboard) m_lastLeaderboard->Hide(m_customPanelFloatingScreen);
        
        m_currentIndex++;
        m_lastLeaderboard = m_customLeaderboards.at(m_currentIndex - 1);
        m_lastLeaderboard->Show(m_customPanelFloatingScreen, m_containerPos, m_platformLeaderboardViewController);

        UpdateButtons();
    }

    void LeaderboardNavigationButtonsController::UpdateButtons() {
        if (m_leftButton && m_leftButton->m_CachedPtr.m_value) m_leftButton->set_interactable(get_leftButtonActive());
        if (m_rightButton && m_rightButton->m_CachedPtr.m_value) m_rightButton->set_interactable(get_rightButtonActive());
    }

    bool LeaderboardNavigationButtonsController::get_ShowDefaultLeaderboard() {
        return  /*m_scoreSaberCustomLeaderboard != null || // SS is not taken into account, so this would always be null, thus always false */ 
                !il2cpp_utils::try_cast<GlobalNamespace::CustomPreviewBeatmapLevel>(m_selectedLevel).has_value() || 
                m_customLeaderboards.size() == 0;
    }

    bool LeaderboardNavigationButtonsController::get_leftButtonActive() {
        return  m_currentIndex > 0 && // index above 0
                (get_ShowDefaultLeaderboard() || m_currentIndex > 1 ) && // we show default or index above 1
                m_leaderboardLoaded &&  // lb loaded
                il2cpp_utils::try_cast<GlobalNamespace::CustomPreviewBeatmapLevel>(m_selectedLevel).has_value(); // current level is custom
    }

    bool LeaderboardNavigationButtonsController::get_rightButtonActive() {
        return  m_currentIndex < m_customLeaderboards.size() && // we are not exceeding the amount of lbs we have
                m_leaderboardLoaded &&  // lb loaded
                il2cpp_utils::try_cast<GlobalNamespace::CustomPreviewBeatmapLevel>(m_selectedLevel).has_value(); // current level is custom

    }

    int LeaderboardNavigationButtonsController::get_leaderboardIndex() {
        int lastLeaderboardIndex = -1;
        auto lbItr = std::find(m_customLeaderboards.begin(), m_customLeaderboards.end(), m_lastLeaderboard);
        if (lbItr != m_customLeaderboards.end()) {
            lastLeaderboardIndex = lbItr - m_customLeaderboards.begin();
        }
        return lastLeaderboardIndex;
    }

}