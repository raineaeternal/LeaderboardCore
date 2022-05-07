#include "Models/UI/ViewControllers/BasicLeaderboardViewController.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"
#include "UnityEngine/UI/VerticalLayoutGroup.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/TextAlignment.hpp"
#include "TMPro/TextMeshPro.hpp"


DEFINE_TYPE(LeaderboardCore::Models::UI::ViewControllers, BasicLeaderboardViewController)

namespace LeaderboardCore::Models::UI::ViewControllers {
    void BasicLeaderboardViewController::DidActivate(bool firstActivation, bool addedToHeirarchy, bool screenSystemDisabling) {
        if (firstActivation) {
            auto horizontal = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(this->get_transform());
            
            horizontal->get_gameObject()->GetComponent<UnityEngine::UI::LayoutElement*>()->set_preferredHeight(70);
            horizontal->get_gameObject()->GetComponent<UnityEngine::UI::LayoutElement*>()->set_preferredWidth(100);

            auto segmentedIconVertical = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(horizontal->get_transform());

            segmentedIconVertical->get_gameObject()->GetComponent<UnityEngine::UI::LayoutElement*>()->set_preferredHeight(20);
            segmentedIconVertical->get_gameObject()->GetComponent<UnityEngine::UI::LayoutElement*>()->set_preferredWidth(9);

            auto leaderboard = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(horizontal->get_transform());

            leaderboard->get_gameObject()->GetComponent<UnityEngine::UI::LayoutElement*>();
        }
    }

    void BasicLeaderboardViewController::Awake() {

    }

    void BasicLeaderboardViewController::SetScores(vector<GlobalNamespace::LeaderboardTableView::ScoreData> scores, int specialScorePos) {

    }
}