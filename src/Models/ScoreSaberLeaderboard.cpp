#include "Models/ScoreSaberLeaderboard.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "UnityEngine/Vector2.hpp"
#include "HMUI/ImageView.hpp"
#include "HMUI/Screen.hpp"
#include "HMUI/HoverHint.hpp"

using namespace UnityEngine;
using namespace UnityEngine::UI;
using namespace HMUI;

namespace LeaderboardCore::Models{
    void ScoreSaberLeaderboard::getScoreSaberComponents(GlobalNamespace::PlatformLeaderboardViewController* plvc){
        if (!isScoreSaberInstalled) return;
        panel = plvc->get_transform()->GetComponentsInChildren<HoverHint*>().FirstOrDefault([](HoverHint* v){
            return v->text == "Opens the ScoreSaber main menu";
        })->get_transform()->get_parent()->get_parent()->get_parent();
        pageUp = plvc->get_transform()->GetComponentsInChildren<Button*>(true).FirstOrDefault([](Button* button){ 
            return reinterpret_cast<RectTransform*>(button->get_transform())->get_anchoredPosition() == Vector2(-40.0f, 20.0f); 
            })->get_transform();
        pageDown = plvc->get_transform()->GetComponentsInChildren<Button*>(true).FirstOrDefault([](Button* button){ 
            return reinterpret_cast<RectTransform*>(button->get_transform())->get_anchoredPosition() == Vector2(-40.0f, -20.0f); 
            })->get_transform();
        infoButtons = plvc->get_transform()->GetComponentsInChildren<ImageView*>(true).FirstOrDefault([](ImageView* view){ 
            return reinterpret_cast<RectTransform*>(view->get_transform())->get_anchoredPosition() == Vector2(45.0f, 26.17f); 
            })->get_transform()->get_parent();
        panelPosition = panel->get_localPosition();
        pageUpPosition = pageUp->get_localPosition();
        pageDownPosition = pageDown->get_localPosition();
        infoButtonsPosition = infoButtons->get_localPosition();
    }
    void ScoreSaberLeaderboard::yeetComponents(){
        if (!isScoreSaberInstalled) return;
        if (pageUp) pageUp->set_localPosition(yeetedPosition);
        if (pageDown) pageDown->set_localPosition(yeetedPosition);
        if (infoButtons) infoButtons->set_localPosition(yeetedPosition);
        if (panel) panel->set_localPosition(yeetedPosition);
    }
    void ScoreSaberLeaderboard::unYeetComponents(){
        if (!isScoreSaberInstalled) return;
        if (pageUp) pageUp->set_localPosition(pageUpPosition);
        if (pageDown) pageDown->set_localPosition(pageDownPosition);
        if (infoButtons) infoButtons->set_localPosition(infoButtonsPosition);
        if (panel) panel->set_localPosition(panelPosition);
    }
}