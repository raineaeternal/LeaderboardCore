#include "main.hpp"
#include "logging.hpp"
#include "_config.hpp"

#include "scotland2/shared/modloader.h"

#include "lapiz/shared/zenject/Zenjector.hpp"
#include "lapiz/shared/utilities/ZenjectExtensions.hpp"

#include "Installers/MenuInstaller.hpp"

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

  zenjector->Install<Installers::MenuInstaller*>(Location::Menu);

  INFO("Installing hooks...");

  INFO("Installed all hooks!");
}