#include "hooking.h"

#include "GlobalNamespace/LeaderboardTableView.hpp"
#include "GlobalNamespace/LeaderboardTableCell.hpp"
#include "HMUI/TableView.hpp"
#include "HMUI/TableCell.hpp"

#include "TMPro/TextMeshProUGUI.hpp"

MAKE_AUTO_HOOK_MATCH(LeaderboardTableView_CellForIdx, &GlobalNamespace::LeaderboardTableView::CellForIdx, HMUI::TableCell*, GlobalNamespace::LeaderboardTableView* self, HMUI::TableView* tableView, int idx) {
    auto tableCell = LeaderboardTableView_CellForIdx(self, tableView, idx);
    // REMOVEME: temp value.
    bool isOST = false;

    if (self->get_transform()->get_parent()->get_parent()->get_name() == "PlatformLeaderboardViewController") {
        GlobalNamespace::LeaderboardTableCell* tableCell = reinterpret_cast<GlobalNamespace::LeaderboardTableCell*>(tableCell);
        TMPro::TextMeshProUGUI* playerNameText = tableCell->playerNameText;

        if (isOST) {
            playerNameText->set_richText(false);
        } else {
            playerNameText->set_richText(true);
        }
    }
    return tableCell;
}