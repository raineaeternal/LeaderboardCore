#include "Installers/LeaderboardCoreMenuInstaller.hpp"

#include "UI/ViewControllers/LeaderboardNavigationButtonsController.hpp"

#include "lapiz/shared/utilities/ZenjectExtensions.hpp"
#include "Zenject/DiContainer.hpp"
#include "Zenject/FromBinderNonGeneric.hpp"
DEFINE_TYPE(LeaderboardCore::Installers, LeaderboardCoreMenuInstaller);

using namespace Lapiz::Zenject::ZenjectExtensions;

namespace LeaderboardCore::Installers {
    void LeaderboardCoreMenuInstaller::InstallBindings() {
        auto container = get_Container();

        FromNewComponentAsViewController(container->BindInterfacesAndSelfTo<LeaderboardCore::UI::ViewControllers::LeaderboardNavigationButtonsController*>())->AsSingle();
    }
}