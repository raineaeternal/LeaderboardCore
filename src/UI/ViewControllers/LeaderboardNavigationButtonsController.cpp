#include "UI/ViewControllers/LeaderboardNavigationButtonsController.hpp"
#include "Hooks/Leaderboard_DidActivate_DidDeactivate.hpp"
#include "Managers/CustomLeaderboardManager.hpp"
#include "LeaderboardCore.hpp"
#include "config.h"
#include "assets.h"
#include "logger.h"
#include "bsml/shared/BSML.hpp"

#include "GlobalNamespace/IDifficultyBeatmap.hpp"
#include "GlobalNamespace/IBeatmapLevel.hpp"
#include "GlobalNamespace/CustomPreviewBeatmapLevel.hpp"
#include "UnityEngine/Quaternion.hpp"
#include "UnityEngine/Vector3.hpp"
#include "HMUI/ViewController_AnimationType.hpp"
#include "HMUI/ViewController_DidActivateDelegate.hpp"

#include "bsml/shared/Helpers/delegates.hpp"
DEFINE_TYPE(LeaderboardCore::UI::ViewControllers, LeaderboardNavigationButtonsController);

namespace LeaderboardCore::UI::ViewControllers {
    void LeaderboardNavigationButtonsController::Inject(GlobalNamespace::PlatformLeaderboardViewController* platformLeaderboardViewController) {
        _platformLeaderboardViewController = platformLeaderboardViewController;
    }

    void LeaderboardNavigationButtonsController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
        DEBUG("DidActivate(firstActivation: {}, addedToHierarchy: {}, screenSystemEnabling: {})", firstActivation, addedToHierarchy, screenSystemEnabling);
        if (!firstActivation) return;
        BSML::parse_and_construct(IncludedAssets::LeaderboardNavigationButtons_bsml, get_transform(), this);
        UpdateButtonsActive();
    }

    void LeaderboardNavigationButtonsController::Initialize() {
        // TODO: the other 3 interface that this type uses must also be implemented as callbacks just like this one
        ::LeaderboardCore::Managers::CustomLeaderboardManager::onLeaderboardsChangedEvent += {&LeaderboardNavigationButtonsController::OnLeaderboardsChanged, this};
        // Something::onScoreSaberActivatedEvent += {&LeaderboardNavigationButtonsController::OnScoreSaberActivated, this};
        ::LeaderboardCore::Events::NotifyLeaderboardSet() += {&LeaderboardNavigationButtonsController::OnLeaderboardSet, this};
        // Something::onLeaderboardLoadedEvent += {&LeaderboardNavigationButtonsController::OnLeaderboardLoaded, this};
        _buttonsFloatingScreen = BSML::FloatingScreen::CreateFloatingScreen({120.0f, 25.0f}, false, {0, 0, 0}, UnityEngine::Quaternion::get_identity());
        
        auto buttonsFloatingScreenTransform = reinterpret_cast<UnityEngine::RectTransform*>(_buttonsFloatingScreen->get_transform());
        buttonsFloatingScreenTransform->SetParent(_platformLeaderboardViewController->get_transform());
        buttonsFloatingScreenTransform->set_localPosition({ 3.0f, 50.0f, 0.0f });
        buttonsFloatingScreenTransform->set_localScale({1, 1, 1});

        auto buttonsFloatingScreenGO = _buttonsFloatingScreen->get_gameObject();
        buttonsFloatingScreenGO->SetActive(false);
        buttonsFloatingScreenGO->SetActive(true);
        buttonsFloatingScreenGO->set_name("LeaderboardNavigationButtonsPanel");

        _customPanelFloatingScreen = BSML::FloatingScreen::CreateFloatingScreen({100.0f, 25.0f}, false, {0, 0, 0}, UnityEngine::Quaternion::get_identity());

        auto customFloatingScreenTransform = reinterpret_cast<UnityEngine::RectTransform*>(_customPanelFloatingScreen->get_transform());
        customFloatingScreenTransform->SetParent(_platformLeaderboardViewController->get_transform());
        customFloatingScreenTransform->set_localPosition({ 3.0f, 50.0f, 0.0f });
        customFloatingScreenTransform->set_localScale({1, 1, 1});

        auto customFloatingScreenGO = _customPanelFloatingScreen->get_gameObject();
        customFloatingScreenGO->SetActive(false);
        customFloatingScreenGO->SetActive(true);
        customFloatingScreenGO->set_name("CustomLeaderboardPanel");
        
        Hooks::PlatformLeaderboardViewControllerEvents::didActivateEvent += {&LeaderboardNavigationButtonsController::OnLeaderboardActivated, this};
        scoreSaberLeaderboard = Models::ScoreSaberLeaderboard(Modloader::getMods().contains("ScoreSaber"));
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
        Hooks::PlatformLeaderboardViewControllerEvents::didActivateEvent -= {&LeaderboardNavigationButtonsController::OnLeaderboardActivated, this};
    }

    void LeaderboardNavigationButtonsController::OnEnable() {
        DEBUG("OnEnable");
        OnLeaderboardLoaded(_leaderboardLoaded);

        if (!_containerTransform || !_containerTransform->m_CachedPtr.m_value) {
            _containerTransform = _platformLeaderboardViewController->get_transform()->Find("Container");
            _containerPosition = _containerTransform->get_localPosition();
            _headerPanelTransform = _platformLeaderboardViewController->get_transform()->Find("HeaderPanel");
            _headerPanelPosition = _headerPanelTransform->get_localPosition();
            OnLeaderboardLoaded(true);
        }
    }

    void LeaderboardNavigationButtonsController::OnLeaderboardActivated(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
        if (!firstActivation) return;
        scoreSaberLeaderboard.getScoreSaberComponents(_platformLeaderboardViewController);
        _buttonsFloatingScreen->SetRootViewController(this, HMUI::ViewController::AnimationType::None);
    }

    void LeaderboardNavigationButtonsController::OnScoreSaberActivated() {
        OnLeaderboardLoaded(true);
    }

    void LeaderboardNavigationButtonsController::OnLeaderboardSet(GlobalNamespace::IDifficultyBeatmap* difficultyBeatmap) {
        DEBUG("Level Set!");
        _selectedLevel = difficultyBeatmap->get_level()->i_IPreviewBeatmapLevel();
        OnLeaderboardLoaded(_leaderboardLoaded);
    }

    void LeaderboardNavigationButtonsController::OnLeaderboardLoaded(bool loaded) {
        DEBUG("OnLeaderboardLoaded({})", loaded);
        _leaderboardLoaded = loaded;
        if (!_selectedLevel || !get_levelIsCustom()) {
            SwitchToDefault();
        } else {
            auto& customLeaderboardsById = Managers::CustomLeaderboardManager::customLeaderboardsById;
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
        DEBUG("SwitchToDefault(lastLeaderboard: {})", lastLeaderboard ? lastLeaderboard->get_LeaderboardId() : "nullptr");
        if (lastLeaderboard) {
            lastLeaderboard->Hide(_customPanelFloatingScreen);
        } else {
            auto& customLeaderboardsById = Managers::CustomLeaderboardManager::customLeaderboardsById;
            auto lbItr = customLeaderboardsById.find(config.lastLeaderboard);
            if (lbItr != customLeaderboardsById.end()) lbItr->second->Hide(_customPanelFloatingScreen);
        }

        _currentIndex = 0;
        UnYeetDefault(); 
    }

    void LeaderboardNavigationButtonsController::SwitchToLastLeaderboard() {
        DEBUG("SwitchToLastLeaderboard()");
        auto& customLeaderboardsById = Managers::CustomLeaderboardManager::customLeaderboardsById;
        auto lbItr = customLeaderboardsById.find(config.lastLeaderboard);
        if (lbItr != customLeaderboardsById.end()) {
            int lastLeaderboardIndex = 0;
            for (const auto& v : Managers::CustomLeaderboardManager::orderedCustomLeaderboards) {
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
            DEBUG("YeetDefault");
            _containerTransform->set_localPosition({-999, -999, -999});
            _headerPanelTransform->set_localPosition({-999, -999, -999});
            scoreSaberLeaderboard.yeetComponents();
        }
    }

    void LeaderboardNavigationButtonsController::UnYeetDefault() {
        if (_containerTransform && _containerTransform->m_CachedPtr.m_value) {
            DEBUG("UnYeetDefault");
            _containerTransform->set_localPosition(_containerPosition);
            _headerPanelTransform->set_localPosition(_headerPanelPosition);
            scoreSaberLeaderboard.unYeetComponents();
        }
    }

    void LeaderboardNavigationButtonsController::LeftButtonClick() {
        if (config.lastLeaderboard.empty()) return;
        auto& customLeaderboardsById = Managers::CustomLeaderboardManager::customLeaderboardsById;
        auto lbItr = customLeaderboardsById.find(config.lastLeaderboard);
        if (lbItr != customLeaderboardsById.end()) {
            lbItr->second->Hide(_customPanelFloatingScreen);
        }
        _currentIndex--;

        if (_currentIndex == 0) {
            UnYeetDefault();
            config.lastLeaderboard.clear();
        } else {
            auto lastLeaderboard = *std::next(Managers::CustomLeaderboardManager::orderedCustomLeaderboards.begin(), _currentIndex - 1);
            config.lastLeaderboard = lastLeaderboard->get_LeaderboardId();
            lastLeaderboard->Show(_customPanelFloatingScreen, _containerPosition, _platformLeaderboardViewController);
        }
        UpdateButtonsActive();
    }

    void LeaderboardNavigationButtonsController::RightButtonClick() {
        DEBUG("RightButtonClick");
        RightButtonClick_overload(nullptr);
    }

    void LeaderboardNavigationButtonsController::RightButtonClick_overload(::LeaderboardCore::Models::CustomLeaderboard* lastLeaderboard) {
        DEBUG("RightButtonClick(RightButtonClick_overload: {})", lastLeaderboard ? lastLeaderboard->get_LeaderboardId() : "nullptr");
        if (_currentIndex == 0) {
            YeetDefault();
        } else {
            if (!lastLeaderboard) {
                auto& customLeaderboardsById = Managers::CustomLeaderboardManager::customLeaderboardsById;
                auto lbItr = customLeaderboardsById.find(config.lastLeaderboard);
                if (lbItr != customLeaderboardsById.end()) {
                    lastLeaderboard = lbItr->second;
                }
            }
            if (lastLeaderboard) lastLeaderboard->Hide(_customPanelFloatingScreen);
        }

        _currentIndex++;
        auto currentLeaderboard = *std::next(Managers::CustomLeaderboardManager::orderedCustomLeaderboards.begin(), _currentIndex - 1);
        config.lastLeaderboard = currentLeaderboard->get_LeaderboardId();
        currentLeaderboard->Show(_customPanelFloatingScreen, _containerPosition, _platformLeaderboardViewController);
        UpdateButtonsActive();
    }

    void LeaderboardNavigationButtonsController::OnLeaderboardsChanged(const std::set<::LeaderboardCore::Models::CustomLeaderboard*>& orderedCustomLeaderboards, const std::unordered_map<std::string, ::LeaderboardCore::Models::CustomLeaderboard*>& customLeaderboardsById) {
        DEBUG("OnLeaderboardsChanged(orderedCustomLeaderboards: {}, customLeaderboardsById: {})", orderedCustomLeaderboards.size(), customLeaderboardsById.size());

        auto lastLeaderboardItr = customLeaderboardsById.find(config.lastLeaderboard);
        auto lastLeaderboard = lastLeaderboardItr != customLeaderboardsById.end() ? lastLeaderboardItr->second : nullptr;

        if (!config.lastLeaderboard.empty() && !customLeaderboardsById.contains(config.lastLeaderboard) && _currentIndex != 0) {
            SwitchToDefault(lastLeaderboard);
        } else if (customLeaderboardsById.contains(config.lastLeaderboard) && _currentIndex == 0) {
            SwitchToLastLeaderboard();
        } else if (_currentIndex == 0 && !get_showDefaultLeaderboard()) {
            RightButtonClick_overload(lastLeaderboard);
        }

        UpdateButtonsActive();
    }

    void LeaderboardNavigationButtonsController::UpdateButtonsActive() {
        if (_leftButton && _leftButton->m_CachedPtr.m_value) _leftButton->get_gameObject()->set_active(get_leftButtonActive());
        if (_rightButton && _rightButton->m_CachedPtr.m_value) _rightButton->get_gameObject()->set_active(get_rightButtonActive());
    }

    bool LeaderboardNavigationButtonsController::get_leftButtonActive() {
        auto result = (_currentIndex > 0 && (get_showDefaultLeaderboard() || _currentIndex > 1 )) && _leaderboardLoaded && get_levelIsCustom();
        DEBUG("get_leftButtonActive -> {}", result);
        return result;
    }

    bool LeaderboardNavigationButtonsController::get_rightButtonActive() {
        auto result = _currentIndex < Managers::CustomLeaderboardManager::orderedCustomLeaderboards.size() && _leaderboardLoaded && get_levelIsCustom();
        DEBUG("get_rightButtonActive -> {}", result);
        return result;
    }

    bool LeaderboardNavigationButtonsController::get_showDefaultLeaderboard() {
        auto result = (!get_levelIsCustom()) || Managers::CustomLeaderboardManager::orderedCustomLeaderboards.empty() || scoreSaberLeaderboard.isScoreSaberInstalled;
        DEBUG("get_showDefaultLeaderboard -> {}", result);
        return result;
    }

    bool LeaderboardNavigationButtonsController::get_levelIsCustom() {
        auto result = il2cpp_utils::try_cast<GlobalNamespace::CustomPreviewBeatmapLevel>(_selectedLevel).has_value();
        DEBUG("get_levelIsCustom -> {}", result);
        return result;
    }

}