#include "UI/ViewControllers/LeaderboardNavigationButtonsController.hpp"
#include "Managers/CustomLeaderboardManager.hpp"
#include "LeaderboardCore.hpp"
#include "config.h"
#include "assets.h"
#include "bsml/shared/BSML.hpp"

#include "GlobalNamespace/IDifficultyBeatmap.hpp"
#include "GlobalNamespace/IBeatmapLevel.hpp"
#include "GlobalNamespace/CustomPreviewBeatmapLevel.hpp"
#include "UnityEngine/Quaternion.hpp"
#include "HMUI/ViewController_AnimationType.hpp"
#include "HMUI/ViewController_DidActivateDelegate.hpp"

#include "bsml/shared/Helpers/delegates.hpp"
DEFINE_TYPE(LeaderboardCore::UI::ViewControllers, LeaderboardNavigationButtonsController);

namespace LeaderboardCore::UI::ViewControllers {
    void LeaderboardNavigationButtonsController::Inject(GlobalNamespace::PlatformLeaderboardViewController* platformLeaderboardViewController) {
        _platformLeaderboardViewController = platformLeaderboardViewController;
    }

    void LeaderboardNavigationButtonsController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
        if (!firstActivation) return;
        BSML::parse_and_construct(IncludedAssets::LeaderboardNavigationButtons_bsml, get_transform(), this);
    }

    void LeaderboardNavigationButtonsController::Initialize() {
        // TODO: the other 3 interface that this type uses must also be implemented as callbacks just like this one
        ::LeaderboardCore::Managers::CustomLeaderboardManager::onLeaderboardsChangedEvent += {&LeaderboardNavigationButtonsController::OnLeaderboardsChanged, this};
        // Something::onScoreSaberActivatedEvent += {&LeaderboardNavigationButtonsController::OnScoreSaberActivated, this};
        ::LeaderboardCore::Events::NotifyLeaderboardSet() += {&LeaderboardNavigationButtonsController::OnLeaderboardSet, this};
        // Something::onLeaderboardLoadedEvent += {&LeaderboardNavigationButtonsController::OnLeaderboardLoaded, this};
        _buttonsFloatingScreen = BSML::FloatingScreen::CreateFloatingScreen({120.0f, 25.0f}, false, {0, 0, 0}, UnityEngine::Quaternion::get_identity());
        
        auto buttonsFloatingScreenTransform = _buttonsFloatingScreen->get_transform();
        buttonsFloatingScreenTransform->SetParent(_platformLeaderboardViewController->get_transform());
        buttonsFloatingScreenTransform->set_localPosition({3.0f, 50.0f, 0});
        buttonsFloatingScreenTransform->set_localScale({1, 1, 1});

        auto buttonsFloatingScreenGO = _buttonsFloatingScreen->get_gameObject();
        buttonsFloatingScreenGO->SetActive(false);
        buttonsFloatingScreenGO->SetActive(true);
        buttonsFloatingScreenGO->set_name("LeaderboardNavigationButtonsPanel");

        _customPanelFloatingScreen = BSML::FloatingScreen::CreateFloatingScreen({100.0f, 25.0f}, false, {0, 0, 0}, UnityEngine::Quaternion::get_identity());

        auto customFloatingScreenTransform = _customPanelFloatingScreen->get_transform();
        customFloatingScreenTransform->SetParent(_platformLeaderboardViewController->get_transform());
        customFloatingScreenTransform->set_localPosition({3.0f, 50.0f, 0});
        customFloatingScreenTransform->set_localScale({1, 1, 1});

        auto customFloatingScreenGO = _customPanelFloatingScreen->get_gameObject();
        customFloatingScreenGO->SetActive(false);
        customFloatingScreenGO->SetActive(true);
        customFloatingScreenGO->set_name("CustomLeaderboardPanel");
        
        auto delegate = BSML::MakeDelegate<::HMUI::ViewController::DidActivateDelegate*>(
            std::function<void(bool, bool, bool)>(
                [this](bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling){ 
                    OnLeaderboardActivated(firstActivation, addedToHierarchy, screenSystemEnabling); 
                }
            )
        );
        _platformLeaderboardViewController->add_didActivateEvent(delegate);
    }

    void LeaderboardNavigationButtonsController::Dispose() {
        // TODO: the other 3 interface that this type uses must also be implemented as callbacks just like this one
        ::LeaderboardCore::Managers::CustomLeaderboardManager::onLeaderboardsChangedEvent -= {&LeaderboardNavigationButtonsController::OnLeaderboardsChanged, this};
        // Something::onScoreSaberActivatedEvent -= {&LeaderboardNavigationButtonsController::OnScoreSaberActivated, this};
        ::LeaderboardCore::Events::NotifyLeaderboardSet() -= {&LeaderboardNavigationButtonsController::OnLeaderboardSet, this};
        // Something::onLeaderboardLoadedEvent -= {&LeaderboardNavigationButtonsController::OnLeaderboardLoaded, this};

        if (_buttonsFloatingScreen && _buttonsFloatingScreen->m_CachedPtr.m_value) {
            UnityEngine::Object::Destroy(_buttonsFloatingScreen->get_gameObject());
        }
    }

    void LeaderboardNavigationButtonsController::OnEnable() {
        OnLeaderboardLoaded(_leaderboardLoaded);

        if (!_containerTransform || !_containerTransform->m_CachedPtr.m_value) {
            _containerTransform = _platformLeaderboardViewController->get_transform()->Find("Container");
            _containerPosition = _containerTransform->get_localPosition();
            OnLeaderboardLoaded(true);
        }
    }

    void LeaderboardNavigationButtonsController::OnLeaderboardActivated(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
        if (firstActivation)
            _buttonsFloatingScreen->SetRootViewController(this, HMUI::ViewController::AnimationType::None);
    }

    void LeaderboardNavigationButtonsController::OnScoreSaberActivated() {
        OnLeaderboardLoaded(true);
    }

    void LeaderboardNavigationButtonsController::OnLeaderboardSet(GlobalNamespace::IDifficultyBeatmap* difficultyBeatmap) {
        _selectedLevel = difficultyBeatmap->get_level()->i_IPreviewBeatmapLevel();
        OnLeaderboardLoaded(_leaderboardLoaded);
    }

    void LeaderboardNavigationButtonsController::OnLeaderboardLoaded(bool loaded) {
        _leaderboardLoaded = loaded;
        if (!_selectedLevel || !get_levelIsCustom()) {
            SwitchToDefault();
        } else {
            if (!loaded || (!config.lastLeaderboard.empty() && !customLeaderboardsById.contains(config.lastLeaderboard) && _currentIndex != 0)) {
                SwitchToDefault();
            } else if (customLeaderboardsById.contains(config.lastLeaderboard) && _currentIndex == 0) {
                SwitchToLastLeaderboard();
            } else if (_currentIndex == 0 && !get_showDefaultLeaderboard()){
                RightButtonClick();
            }
        }

        UpdateButtonsActive();
    }

    void LeaderboardNavigationButtonsController::SwitchToDefault(::LeaderboardCore::Models::CustomLeaderboard* lastLeaderboard) {
        if (lastLeaderboard) {
            lastLeaderboard->Hide(_customPanelFloatingScreen);
        } else {
            auto lbItr = customLeaderboardsById.find(config.lastLeaderboard);
            if (lbItr != customLeaderboardsById.end()) lbItr->second->Hide(_customPanelFloatingScreen);
        }

        _currentIndex = 0;
        UnYeetDefault(); 
    }

    void LeaderboardNavigationButtonsController::SwitchToLastLeaderboard() {
        auto lbItr = customLeaderboardsById.find(config.lastLeaderboard);
        if (lbItr != customLeaderboardsById.end()) {
            int lastLeaderboardIndex = 0;
            for (const auto& v : orderedCustomLeaderboards) {
                if (v == lbItr->second) break;
                lastLeaderboardIndex++;
            }
            lbItr->second->Show(_customPanelFloatingScreen, _containerPosition, _platformLeaderboardViewController);
            _currentIndex = lastLeaderboardIndex + 1;
            YeetDefault();
        }
    }

    void LeaderboardNavigationButtonsController::YeetDefault() {
        if (_containerTransform && _containerTransform->m_CachedPtr.m_value) {
            _containerTransform->set_localPosition({-999, -999, -999});
        }
    }

    void LeaderboardNavigationButtonsController::UnYeetDefault() {
        if (_containerTransform && _containerTransform->m_CachedPtr.m_value) {
            _containerTransform->set_localPosition(_containerPosition);
        }
    }

    void LeaderboardNavigationButtonsController::LeftButtonClick() {
        if (config.lastLeaderboard.empty()) return;
        auto lbItr = customLeaderboardsById.find(config.lastLeaderboard);
        if (lbItr != customLeaderboardsById.end()) {
            lbItr->second->Hide(_customPanelFloatingScreen);
        }
        _currentIndex--;

        if (_currentIndex == 0) {
            UnYeetDefault();
            config.lastLeaderboard.clear();
        } else {
            auto lastLeaderboard = *std::next(orderedCustomLeaderboards.begin(), _currentIndex - 1);
            config.lastLeaderboard = lastLeaderboard->get_LeaderboardId();
            lastLeaderboard->Show(_customPanelFloatingScreen, _containerPosition, _platformLeaderboardViewController);
        }
        UpdateButtonsActive();
    }

    void LeaderboardNavigationButtonsController::RightButtonClick() {
        RightButtonClick_overload(nullptr);
    }

    void LeaderboardNavigationButtonsController::RightButtonClick_overload(::LeaderboardCore::Models::CustomLeaderboard* lastLeaderboard) {
        if (_currentIndex == 0) {
            YeetDefault();
        } else {
            if (!lastLeaderboard) {
                auto lbItr = customLeaderboardsById.find(config.lastLeaderboard);
                if (lbItr != customLeaderboardsById.end()) {
                    lastLeaderboard = lbItr->second;
                }
            }
            if (lastLeaderboard) lastLeaderboard->Hide(_customPanelFloatingScreen);
        }

        _currentIndex++;
        auto currentLeaderboard = *std::next(orderedCustomLeaderboards.begin(), _currentIndex - 1);
        config.lastLeaderboard = currentLeaderboard->get_LeaderboardId();
        currentLeaderboard->Show(_customPanelFloatingScreen, _containerPosition, _platformLeaderboardViewController);
        UpdateButtonsActive();
    }

    void LeaderboardNavigationButtonsController::OnLeaderboardsChanged(const std::set<::LeaderboardCore::Models::CustomLeaderboard*>& orderedCustomLeaderboards, const std::unordered_map<std::string, ::LeaderboardCore::Models::CustomLeaderboard*>& customLeaderboardsById) {
        this->orderedCustomLeaderboards.clear();
        this->orderedCustomLeaderboards.insert(orderedCustomLeaderboards.begin(), orderedCustomLeaderboards.end());

        auto lastLeaderboardItr = this->customLeaderboardsById.find(config.lastLeaderboard);
        auto lastLeaderboard = lastLeaderboardItr != this->customLeaderboardsById.end() ? lastLeaderboardItr->second : nullptr;
        this->customLeaderboardsById.clear();
        for (const auto& [id, leaderboard] : customLeaderboardsById) {
            this->customLeaderboardsById.emplace(id, leaderboard);
        }

        if (!config.lastLeaderboard.empty() && !this->customLeaderboardsById.contains(config.lastLeaderboard) && _currentIndex != 0) {
            SwitchToDefault(lastLeaderboard);
        } else if (this->customLeaderboardsById.contains(config.lastLeaderboard) && _currentIndex == 0) {
            SwitchToLastLeaderboard();
        } else if (_currentIndex == 0 && !get_showDefaultLeaderboard()) {
            RightButtonClick_overload(lastLeaderboard);
        }

        UpdateButtonsActive();
    }

    void LeaderboardNavigationButtonsController::UpdateButtonsActive() {
        if (_leftButton && _leftButton->m_CachedPtr.m_value) _leftButton->set_interactable(get_leftButtonActive());
        if (_rightButton && _rightButton->m_CachedPtr.m_value) _rightButton->set_interactable(get_rightButtonActive());
    }

    bool LeaderboardNavigationButtonsController::get_leftButtonActive() {
        return (_currentIndex > 0 && (get_showDefaultLeaderboard() || _currentIndex > 1 )) && _leaderboardLoaded && get_levelIsCustom();
    }

    bool LeaderboardNavigationButtonsController::get_rightButtonActive() {
        return _currentIndex < orderedCustomLeaderboards.size() && _leaderboardLoaded && get_levelIsCustom();
    }

    bool LeaderboardNavigationButtonsController::get_showDefaultLeaderboard() {
        return !(get_levelIsCustom()) || orderedCustomLeaderboards.empty();
    }

    bool LeaderboardNavigationButtonsController::get_levelIsCustom() {
        return il2cpp_utils::try_cast<GlobalNamespace::CustomPreviewBeatmapLevel>(_selectedLevel).has_value();
    }

}