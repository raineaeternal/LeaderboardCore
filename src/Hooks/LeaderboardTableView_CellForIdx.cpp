#include "hooking.h"
#include "logger.h"

#include "GlobalNamespace/LeaderboardTableView.hpp"
#include "GlobalNamespace/LeaderboardTableCell.hpp"
#include "HMUI/TableView.hpp"
#include "HMUI/TableCell.hpp"

#include "TMPro/TextMeshProUGUI.hpp"

// MAKE_AUTO_HOOK_MATCH(LeaderboardTableView_CellForIdx, &GlobalNamespace::LeaderboardTableView::CellForIdx, HMUI::TableCell*, GlobalNamespace::LeaderboardTableView* self, HMUI::TableView* tableView, int idx) {
//     auto tableCell = LeaderboardTableView_CellForIdx(self, tableView, idx);
//     // REMOVEME: temp value.
//     bool isOST = false;

//     auto vcName = self->get_transform()->get_parent()->get_parent()->get_name();

//     if (vcName == "PlatformLeaderboardViewController") {
//         DEBUG("{}'s name was == to the PlatformLeaderboardViewController!", vcName);
//         GlobalNamespace::LeaderboardTableCell* tableCell = reinterpret_cast<GlobalNamespace::LeaderboardTableCell*>(tableCell);
//         DEBUG("tablecell casted to LeaderboardTableCell");
//         TMPro::TextMeshProUGUI* playerNameText = tableCell->playerNameText;
//         DEBUG("Got {} from {}", fmt::ptr(playerNameText), fmt::ptr(tableCell->playerNameText));

//         if (isOST) {
//             playerNameText->set_richText(false);
//             DEBUG("Set rich text to false!");
//         } else {
//             playerNameText->set_richText(true);
//             DEBUG("Set rich text to true!");
//         }
//     }
//     return tableCell;
// }