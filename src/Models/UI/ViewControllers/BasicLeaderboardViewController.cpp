#include "GlobalNamespace/LeaderboardTableView.hpp"

#include "Models/UI/ViewControllers/BasicLeaderboardViewController.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"
#include "UnityEngine/UI/VerticalLayoutGroup.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/TextAlignment.hpp"
#include "TMPro/TextMeshPro.hpp"

#include "include/Base64CaratStrings.hpp"


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

            auto pageButtonUp = QuestUI::BeatSaberUI::CreateClickableImage(horizontal->get_transform(), QuestUI::BeatSaberUI::Base64ToSprite(carat_up), [](){

            });

            auto pageButtonDown = QuestUI::BeatSaberUI::CreateClickableImage(horizontal->get_transform(), QuestUI::BeatSaberUI::Base64ToSprite(carat_down), [](){

            });
        }
    }

    void BasicLeaderboardViewController::Awake() {

    }

    void BasicLeaderboardViewController::SetScores(std::vector<GlobalNamespace::LeaderboardTableView::ScoreData> scores, int specialScorePos) {
        
    }
}