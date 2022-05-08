#pragma once

#include "custom-types/shared/macros.hpp"
#include "HMUI/SegmentedControl.hpp"
#include "HMUI/IconSegmentedControl.hpp"
#include "HMUI/IconSegmentedControl_DataItem.hpp"
#include "HMUI/IconSegmentedControlCell.hpp"
using namespace HMUI;

#include "UnityEngine/Sprite.hpp"
#include "UnityEngine/GameObject.hpp"

DECLARE_CLASS_CODEGEN(LeaderboardCore, IconSegmentedControlImpl,
    DECLARE_INSTANCE_FIELD(SegmentedControl*, segmentedControl);

    DECLARE_INSTANCE_FIELD(IconSegmentedControlCell*, firstCellPrefab);
    DECLARE_INSTANCE_FIELD(IconSegmentedControlCell*, lastCellPrefab);
    DECLARE_INSTANCE_FIELD(IconSegmentedControlCell*, singleCellPrefab);
    DECLARE_INSTANCE_FIELD(IconSegmentedControlCell*, middleCellPrefab);
    DECLARE_INSTANCE_FIELD(ArrayW<UnityEngine::Sprite*>, icons)

    DECLARE_OVERRIDE_METHOD(int, NumberOfCells, il2cpp_utils::il2cpp_type_check::MetadataGetter<&SegmentedControl::IDataSource::NumberOfCells>::get());
    DECLARE_OVERRIDE_METHOD(SegmentedControlCell*, CellForCellNumber, il2cpp_utils::il2cpp_type_check::MetadataGetter<&SegmentedControl::IDataSource::CellForCellNumber>::get());
    DECLARE_CTOR(ctor);
    DECLARE_DTOR(dtor);
    public:
        void set_icons(ArrayW<UnityEngine::Sprite*> iconsList);
        void add_icon(UnityEngine::Sprite* addedIcons);

        float iconSize = 4.0f;
        bool hideCellBG = false;
        bool overrideCellSize = false;
        float padding = 2.0f;

    private:
        IconSegmentedControlCell* InstantiateCell(UnityEngine::GameObject* prefab)

)