#include "include/UIElements/IconSegmentedControlImpl.hpp"
#include "HMUI/TextSegmentedControlCell.hpp"
#include "UnityEngine/RectTransform.hpp"

DEFINE_TYPE(LeaderboardCore::UI, IconSegmentedControlImpl);

namespace LeaderboardCore::UI {
    void IconSegmentedControlImpl::ctor() {
        INVOKE_CTOR();
        icons = ArrayW<UnityEngine::Sprite*>(static_cast<il2cpp_array_size_t>(0));
    }

    void IconSegmentedControlImpl::dtor() {
        Finalize();
    }

    int IconSegmentedControlImpl::NumberOfCells() {
        return icons.size();
    }

    HMUI::SegmentedControlCell* IconSegmentedControlImpl::CellForCellNumber(int cellNumber) {
        HMUI::IconSegmentedControlCell *result = nullptr;
        if (icons.size() == 1) {
            result = reinterpret_cast<HMUI::IconSegmentedControlCell *>(InstantiateCell(
                    singleCellPrefab->get_gameObject()));
        } else if (cellNumber == 0) {
            result = reinterpret_cast<HMUI::IconSegmentedControlCell *>(InstantiateCell(
                    firstCellPrefab->get_gameObject()));
        } else if (cellNumber == icons.size() - 1) {
            result = reinterpret_cast<HMUI::IconSegmentedControlCell *>(InstantiateCell(
                    lastCellPrefab->get_gameObject()));
        } else {
            result = reinterpret_cast<HMUI::IconSegmentedControlCell *>(InstantiateCell(
                    middleCellPrefab->get_gameObject()));
        }
        result->set_sprite(icons[cellNumber]);
        result->set_hideBackgroundImage(hideCellBG);
        return result;
    }

    void IconSegmentedControlImpl::set_icons(ArrayW<UnityEngine::Sprite *> iconsList) {
        icons = iconsList;
        if (segmentedControl) segmentedControl->ReloadData();
    }

    void IconSegmentedControlImpl::add_icon(UnityEngine::Sprite *addedIcons) {
        int len = icons.size();
        ArrayW<UnityEngine::Sprite*> newicons(len);
        icons = newicons;
        icons[len] = addedIcons;
        if(segmentedControl) segmentedControl->ReloadData();
    }

    HMUI::IconSegmentedControlCell* IconSegmentedControlImpl::InstantiateCell(UnityEngine::GameObject* prefab) {
        auto gameObject = Object::Instantiate(prefab, {0, 0, 0}, UnityEngine::Quaternion::get_identity(), get_transform());
        gameObject->get_transform()->set_localScale({1, 1, 1});
        return gameObject->GetComponent<HMUI::IconSegmentedControlCell*>();
    }
}