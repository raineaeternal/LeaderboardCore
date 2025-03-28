#pragma once

#include "custom-types/shared/macros.hpp"
#include "HMUI/NavigationController.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "Zenject/IInitializable.hpp"
#include "System/IDisposable.hpp"

DECLARE_CLASS_CODEGEN_INTERFACES(LeaderboardCore::UI, LeaderboardNavigationController, HMUI::NavigationController, Zenject::IInitializable*, System::IDisposable*) {

    DECLARE_OVERRIDE_METHOD_MATCH(void, DidActivate, &HMUI::ViewController::DidActivate, bool, bool, bool);
    DECLARE_OVERRIDE_METHOD_MATCH(void, DidDeactivate, &HMUI::ViewController::DidDeactivate, bool, bool);

    DECLARE_INSTANCE_METHOD(bool, get_leftButtonActive);
    DECLARE_INSTANCE_METHOD(bool, get_rightButtonActive);

    DECLARE_INSTANCE_METHOD(void, LeftButtonClick);
    DECLARE_INSTANCE_METHOD(void, RightButtonClick);

    DECLARE_OVERRIDE_METHOD_MATCH(void, Initialise, &Zenject::IInitializable::Initialize);
    DECLARE_OVERRIDE_METHOD_MATCH(void, Dispose, &System::IDisposable::Dispose);

    DECLARE_INSTANCE_METHOD(void, PostParse);

    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button*, _leftButton);
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button*, _rightButton);
};
