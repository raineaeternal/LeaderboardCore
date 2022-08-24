#include "GlobalNamespace/LeaderboardTableView.hpp"

#include "Models/UI/ViewControllers/BasicLeaderboardViewController.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"
#include "UnityEngine/UI/VerticalLayoutGroup.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/TextAlignment.hpp"
#include "TMPro/TextMeshPro.hpp"

#include "bsml/shared/BSML.hpp"
#include "assets.hpp"

#include "include/Base64CaratStrings.hpp"

#include "main.hpp"


DEFINE_TYPE(LeaderboardCore::Models::UI::ViewControllers, BasicLeaderboardViewController)

namespace LeaderboardCore::Models::UI::ViewControllers {
    void BasicLeaderboardViewController::DidActivate(bool firstActivation, bool addedToHeirarchy, bool screenSystemDisabling) {
        if (!firstActivation) return;
        BSML::parse_and_construct(IncludedAssets::BasicLeaderboardViewController_bsml, get_transform(), this);
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