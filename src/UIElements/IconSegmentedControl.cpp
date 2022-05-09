#include "include/UIElements/IconSegmentedControlImpl.hpp"

DEFINE_TYPE(LeaderboardCore, IconSegmentedControlImpl);

namespace LeaderboardCore::UI {
    void IconSegmentedControlImpl::ctor() {
        INVOKE_CTOR();
        icons = ArrayW<UnityEngine::Sprite*>(static_cast<il2cpp_array_size_t>(0));
    }

    int IconSegmentedControlImpl::NumberOfCells() {
        return icons.Count();
    }

    HMUI::SegmentedControlCell* IconSegmentedControl::CellForCellNumber(int idx) {
        HMUI::IconSegmentedControlCell* result = nullptr;
        if (icons.Count() == 1) {
            result = reinterpret_cast<HMUI::TextSegmentedControlCell*>(InstantiateCell(singleCellPrefab->get_gameObject()));
        }
        else if (idx == 0) {
            result = reinterpret_cast<HMUI::TextSegmentedControlCell*>(InstantiateCell(firstCellPrefab->get_gameObject()));
        } 
        else if (idx == icons.Count() - 1) {
            result = reinterpret_cast<HMUI::TextSegmentedControlCell*>(InstantiateCell(lastCellPrefab->get_gameObject()));
        }
        else {
            result = reinterpret_cast<HMUI::TextSegmentedControlCell*>(InstantiateCell(middleCellPrefab->get_gameObject()));
        }

        result->set_fontSize(fontSize);
        result->set_icons(icons[idx]);
        result->set_hideBackgroundImage(hideCellBG);

        void CustomTextSegmentedControlData::set_texts(ArrayW<StringW> list) {
            texts = list;
            if (segmentedControl) segmentedControl->ReloadData();
        }

        void CustomTextSegmentedControlData::add_text() {
            
        }

        HMUI::IconSegmentedControlCell* IconSegmentedControlImpl::InstantiateCell(UnityEngine::GameObject* prefab) {
            auto gameObject = Object::Instantiate(prefab, {0, 0, 0}, Quaternion::get_identity(), get_transform());
            gameObject->get_transform()->set_localScale({1, 1, 1});
            return gameObject->GetComponent<HMUI::TextSegmentedControlCell*>();
        }
    }
}