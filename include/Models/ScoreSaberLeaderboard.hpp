#pragma once
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Vector3.hpp"
#include "GlobalNamespace/PlatformLeaderboardViewController.hpp"
#include "modloader/shared/modloader.hpp"

namespace LeaderboardCore::Models{

    class ScoreSaberLeaderboard{
        public:
        void getScoreSaberComponents(GlobalNamespace::PlatformLeaderboardViewController* plvc);
        void yeetComponents();
        void unYeetComponents();
        bool isScoreSaberInstalled;
        ScoreSaberLeaderboard(bool installed) : isScoreSaberInstalled(installed){}
        private:
        UnityEngine::Transform* pageUp;
        UnityEngine::Transform* pageDown;
        UnityEngine::Transform* infoButtons;
        UnityEngine::Transform* panel;
        UnityEngine::Vector3 pageUpPosition;
        UnityEngine::Vector3 pageDownPosition;
        UnityEngine::Vector3 infoButtonsPosition;
        UnityEngine::Vector3 panelPosition;
        UnityEngine::Vector3 yeetedPosition = UnityEngine::Vector3(-999, -999, -999);
    };
}