#pragma once

#include "UnityEngine/MonoBehaviour.hpp"
#include "custom-types/shared/macros.hpp"
#include "HMUI/ViewController.hpp"
#include "GlobalNamespace/LeaderboardTableView_ScoreData.hpp"
#include "HMUI/IconSegmentedControl.hpp"
#include "HMUI/IconSegmentedControl_DataItem.hpp"

#include <vector>

#define GET_FIND_METHOD(mPtr) il2cpp_utils::il2cpp_type_check::MetadataGetter<mPtr>::get()


DECLARE_CLASS_CODEGEN(LeaderboardCore::Models::UI::ViewControllers, BasicLeaderboardViewController, HMUI::ViewController,
    DECLARE_OVERRIDE_METHOD(void, DidActivate, GET_FIND_METHOD(&HMUI::ViewController::DidActivate), bool firstActivation, bool addedToHeirarchy, bool screenSystemDisabling);
    DECLARE_INSTANCE_METHOD(void, Awake);
    public:
        GlobalNamespace::LeaderboardTableView table;

        std::vector<HMUI::IconSegmentedControl::DataItem*> cellData;

        void SetScores(std::vector<GlobalNamespace::LeaderboardTableView::ScoreData> scores, int specialScorePos);
)