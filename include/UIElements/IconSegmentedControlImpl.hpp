#pragma once

#include "custom-types/shared/macros.hpp"
#include "HMUI/SegmentedControl.hpp"
#include "HMUI/IconSegmentedControl.hpp"
#include "HMUI/IconSegmentedControl_DataItem.hpp"
#include "HMUI/IconSegmentedControlCell.hpp"


#include "UnityEngine/Sprite.hpp"
#include "UnityEngine/GameObject.hpp"

___DECLARE_TYPE_WRAPPER_INHERITANCE(LeaderboardCore, IconSegmentedControlImpl, Il2CppTypeEnum::IL2CPP_TYPE_CLASS, UnityEngine::MonoBehaviour, "LeaderboardCore", { classof(HMUI::SegmentedControl::IDataSource*) }, 0, nullptr,
    DECLARE_INSTANCE_FIELD(SegmentedControl*, segmentedControl);

    DECLARE_INSTANCE_FIELD(HMUI::IconSegmentedControlCell*, firstCellPrefab);
    DECLARE_INSTANCE_FIELD(HMUI::IconSegmentedControlCell*, lastCellPrefab);
    DECLARE_INSTANCE_FIELD(HMUI::IconSegmentedControlCell*, singleCellPrefab);
    DECLARE_INSTANCE_FIELD(HMUI::IconSegmentedControlCell*, middleCellPrefab);
    DECLARE_INSTANCE_FIELD(HMUI::ArrayW<UnityEngine::Sprite*>, icons)

    DECLARE_OVERRIDE_METHOD(int, NumberOfCells, il2cpp_utils::il2cpp_type_check::MetadataGetter<&SegmentedControl::IDataSource::NumberOfCells>::get());
    DECLARE_OVERRIDE_METHOD(HMUI::SegmentedControlCell*, CellForCellNumber, il2cpp_utils::il2cpp_type_check::MetadataGetter<&SegmentedControl::IDataSource::CellForCellNumber>::get());
    DECLARE_CTOR();

    public:
        void set_icons(ArrayW<UnityEngine::Sprite*> iconsList);
        void add_icon(UnityEngine::Sprite* addedIcons);

        float iconSize = 4.0f;
        bool hideCellBG = false;
        bool overrideCellSize = false;
        float padding = 2.0f;

    private:
        HMUI::IconSegmentedControlCell* InstantiateCell(UnityEngine::GameObject* prefab)
)