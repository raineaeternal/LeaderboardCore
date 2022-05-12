#include "GlobalNamespace/LeaderboardTableView.hpp"

#include "Models/UI/ViewControllers/BasicLeaderboardViewController.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"
#include "UnityEngine/UI/VerticalLayoutGroup.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/TextAlignment.hpp"
#include "TMPro/TextMeshPro.hpp"
#include "include/UIElements/LoadingControl.hpp"
#include "include/UIElements/LeaderboardComponent.hpp"

#include "include/Base64CaratStrings.hpp"

#include "main.hpp"


DEFINE_TYPE(LeaderboardCore::Models::UI::ViewControllers, BasicLeaderboardViewController)

namespace LeaderboardCore::Models::UI::ViewControllers {
    void BasicLeaderboardViewController::DidActivate(bool firstActivation, bool addedToHeirarchy, bool screenSystemDisabling) {
        if (firstActivation) {
            auto horizontal = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(this->get_transform());
            
            horizontal->get_gameObject()
                      ->GetComponent<UnityEngine::UI::LayoutElement*>()
                      ->set_preferredHeight(70);
            horizontal->get_gameObject()
                      ->GetComponent<UnityEngine::UI::LayoutElement*>()
                      ->set_preferredWidth(100);

            auto segmentedIconVertical = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(horizontal->get_transform());

            segmentedIconVertical->get_gameObject()
                                 ->GetComponent<UnityEngine::UI::LayoutElement*>()
                                 ->set_preferredHeight(20);
            segmentedIconVertical->get_gameObject()
                                 ->GetComponent<UnityEngine::UI::LayoutElement*>()
                                 ->set_preferredWidth(9);

            auto leaderboardLayoutGroup = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(horizontal->get_transform());

            leaderboardLayoutGroup->get_gameObject()
                                  ->GetComponent<UnityEngine::UI::LayoutElement*>()
                                  ->set_preferredHeight(70);
            leaderboardLayoutGroup->get_gameObject()
                                  ->GetComponent<UnityEngine::UI::LayoutElement*>()
                                  ->set_preferredWidth(80);

            auto leaderboard = LeaderboardCore::UI::Elements::CreateLeaderboardComponent(leaderboardLayoutGroup->get_transform());
            leaderboard->GetComponent<GlobalNamespace::LeaderboardTableView*>()->rowHeight = 5.99f;

            auto loadingControl = LeaderboardCore::UI::Elements::CreateLoadingIndicator(leaderboardLayoutGroup->get_transform(), UnityEngine::Vector2(0, 0));

            auto pageButtonUp = QuestUI::BeatSaberUI::CreateClickableImage(horizontal->get_transform(), QuestUI::BeatSaberUI::Base64ToSprite(carat_up), [](){

            });

            auto pageButtonDown = QuestUI::BeatSaberUI::CreateClickableImage(horizontal->get_transform(), QuestUI::BeatSaberUI::Base64ToSprite(carat_down), [](){

            });
        }
    }

    void BasicLeaderboardViewController::Awake() {

    }

    void BasicLeaderboardViewController::SetScores(List<GlobalNamespace::LeaderboardTableView::ScoreData*>* scores, int specialScorePos) {
        if (table) {
            table->SetScores(scores, specialScorePos);
            isLoaded = true;
        } else {
            getLogger().warning("Tried to set scores when there are no tables available!");
        }
    }
}