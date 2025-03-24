#include "main.hpp"
#include "UI/LeaderboardNavigationController.hpp"
#include "UI/PlatformLeaderboardViewController.hpp"
#include "lapiz/shared/zenject/Location.hpp"
#include "logging.hpp"
#include "_config.hpp"

#include "scotland2/shared/modloader.h"

#include "lapiz/shared/zenject/Zenjector.hpp"
#include "lapiz/shared/utilities/ZenjectExtensions.hpp"

using namespace LeaderboardCore;

static modloader::ModInfo modInfo{MOD_ID, VERSION, 0};

// Called at the early stages of game loading
LBCORE_EXPORT_FUNC void setup(CModInfo *info) noexcept {
  *info = modInfo.to_c();

  INFO("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
LBCORE_EXPORT_FUNC void late_load() noexcept {
  il2cpp_functions::Init();

  using namespace Lapiz::Zenject;
  using namespace Lapiz::Zenject::ZenjectExtensions;

  auto zenjector = Zenjector::Get();

  zenjector->Install(Location::Menu, [](::Zenject::DiContainer *container) {
    container->BindInterfacesAndSelfTo<UI::CustomPlatformLeaderboardViewController*>();
    container->BindInterfacesAndSelfTo<UI::LeaderboardNavigationController*>();
  });

  INFO("Installing hooks...");

  INFO("Installed all hooks!");
}