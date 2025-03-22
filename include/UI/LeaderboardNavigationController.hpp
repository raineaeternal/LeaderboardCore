#pragma once

#include "custom-types/shared/macros.hpp"
#include "HMUI/NavigationController.hpp"

DECLARE_CLASS_CODEGEN(LeaderboardCore::UI, LeaderboardNavigationController, HMUI::NavigationController) {
    DECLARE_OVERRIDE_METHOD_MATCH(void, DidActivate, &HMUI::ViewController::DidActivate, bool, bool, bool);
    DECLARE_OVERRIDE_METHOD_MATCH(void, DidDeactivate, &HMUI::ViewController::DidDeactivate, bool, bool);
};

