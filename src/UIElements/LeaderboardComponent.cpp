#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Resources.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "UIElements/LeaderboardComponent.hpp"
#include "GlobalNamespace/LeaderboardTableView.hpp"
#include "GlobalNamespace/LeaderboardTableCell.hpp"
#include "VRUIControls/VRGraphicRaycaster.hpp"
#include "questui/shared/BeatSaberUI.hpp"

namespace LeaderboardCore::UI::Elements {
    UnityEngine::GameObject* CreateLeaderboardComponent(UnityEngine::Transform* parent) {
        auto leaderboardTemplate = UnityEngine::Resources::FindObjectsOfTypeAll<GlobalNamespace::LeaderboardTableView*>().First([](GlobalNamespace::LeaderboardTableView* x){ return x->get_name() == "LeaderboardTableView"; });
        auto table = UnityEngine::Object::Instantiate(leaderboardTemplate, parent, false);
        table->set_name("LeaderboardCoreLeaderboardComponent");
        table->cellPrefab->scoreText->set_enableWordWrapping(false);
        table->GetComponent<VRUIControls::VRGraphicRaycaster*>()->physicsRaycaster = QuestUI::BeatSaberUI::GetPhysicsRaycasterWithCache();
        for(GlobalNamespace::LeaderboardTableCell* tableCell : table->GetComponentsInChildren<GlobalNamespace::LeaderboardTableCell*>())
            UnityEngine::Object::Destroy(tableCell->get_gameObject());
        return table->get_gameObject();
    }
}