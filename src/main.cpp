#include "main.hpp"
#include "logging.hpp"
#include "_config.hpp"

#include "scotland2/shared/modloader.h"

static modloader::ModInfo modInfo{MOD_ID, VERSION, 0};

// Called at the early stages of game loading
LBCORE_EXPORT_FUNC void setup(CModInfo *info) noexcept {
  *info = modInfo.to_c();

  INFO("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
LBCORE_EXPORT_FUNC void late_load() noexcept {
  il2cpp_functions::Init();

  INFO("Installing hooks...");

  INFO("Installed all hooks!");
}