#include "main.hpp"
#include "custom-types/shared/register.hpp"
#include "logger.h"
#include "hooking.h"

#include "Installers/LeaderboardCoreMenuInstaller.hpp"
#include "lapiz/shared/zenject/Zenjector.hpp"
#include "bsml/shared/BSML.hpp"

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use
Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

namespace LeaderboardCore {
    Logger& Logging::getLogger() {
        static Logger* logger = new Logger(modInfo);
        return *logger;
    }
}

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) { 
    info.id = MOD_ID;
    info.version = VERSION;
    modInfo = info;
	
    getConfig().Load(); // Load the config file
    INFO("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();
    custom_types::Register::AutoRegister();
    BSML::Init();

    Hooks::InstallHooks(LeaderboardCore::Logging::getLogger());
    auto zenjector = Lapiz::Zenject::Zenjector::Get();
    zenjector->Install<LeaderboardCore::Installers::LeaderboardCoreMenuInstaller*>(Lapiz::Zenject::Location::Menu);
}