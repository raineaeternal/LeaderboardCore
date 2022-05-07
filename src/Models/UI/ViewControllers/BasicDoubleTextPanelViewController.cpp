#include "Models/UI/ViewControllers/BasicDoubleTextPanelViewController.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"
#include "UnityEngine/UI/VerticalLayoutGroup.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/TextAlignment.hpp"
#include "TMPro/TextMeshPro.hpp"

DEFINE_TYPE(LeaderboardCore::Models::UI::ViewControllers, BasicDoubleTextPanelViewController)

namespace LeaderboardCore::Models::UI::ViewControllers {
    void BasicDoubleTextPanelViewController::DidActivate(bool firstActivation, bool addedToHeirarchy, bool screenSystemDisabling) {
        if (firstActivation) {
            auto vertical = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(this->get_transform());
            vertical->get_gameObject()->GetComponent<QuestUI::Backgroundable*>()->ApplyBackground("round-rect-panel");
            
            vertical->set_spacing(1);
            vertical->get_gameObject()->GetComponent<UnityEngine::UI::LayoutElement*>()->set_preferredHeight(10);
            vertical->get_gameObject()->GetComponent<UnityEngine::UI::LayoutElement*>()->set_preferredWidth(70);
            vertical->set_childForceExpandHeight(false);
            vertical->set_childForceExpandWidth(false);

            auto clickTextTop = QuestUI::BeatSaberUI::CreateClickableText(vertical->get_transform(), "Placeholder Text", [] () {
                
            });

            clickTextTop->set_alignment(UnityEngine::TextAlignment::Left);
            clickTextTop->set_fontSize(3.5f);

            auto nonClickTextTop = QuestUI::BeatSaberUI::CreateText(vertical->get_transform(), "Placeholder Text");

            nonClickTextTop->set_alignment(UnityEngine::TextAlignment::Left);
            nonClickTextTop->set_fontSize(3.5f);

            auto clickTextBottom = QuestUI::BeatSaberUI::CreateClickableText(vertical->get_transform(), "Placeholder Text", [] () {
                
            });

            clickTextBottom->set_alignment(UnityEngine::TextAlignment::Left);
            clickTextBottom->set_fontSize(3.5f);

            auto nonClickTextBottom = QuestUI::BeatSaberUI::CreateText(vertical->get_transform(), "Placeholder Text");

            nonClickTextBottom->set_alignment(UnityEngine::TextAlignment::Left);
            nonClickTextBottom->set_fontSize(3.5f);
        }
    }
}