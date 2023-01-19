#include "Managers/CustomLeaderboardManager.hpp"
#include "Models/CustomLeaderboard.hpp"
#include "logger.h"

namespace LeaderboardCore::Managers {
    std::unordered_set<Interfaces::INotifyLeaderboardChange*> CustomLeaderboardManager::notifyCustomLeaderboardsChanges;
    std::unordered_map<std::string, Models::CustomLeaderboard*> CustomLeaderboardManager::customLeaderboardsById;
    std::set<Models::CustomLeaderboard*> CustomLeaderboardManager::orderedCustomLeaderboards;

    UnorderedEventCallback<const std::set<Models::CustomLeaderboard*>&, const std::unordered_map<std::string, Models::CustomLeaderboard*>&> CustomLeaderboardManager::onLeaderboardsChangedEvent;

    void CustomLeaderboardManager::Register(Models::CustomLeaderboard* customLeaderboard, const ModInfo& modInfo) {
        customLeaderboard->pluginId = modInfo.id;
        auto id = customLeaderboard->get_LeaderboardId();
        if (!customLeaderboardsById.contains(id)) {
            INFO("Registering leaderboard with ID '{}'", id);
            customLeaderboardsById[id] = customLeaderboard;
            
            OnLeaderboardsChanged();
        } else {
            ERROR("Tried Registering a leaderboard with ID '{}' twice!", id);
        }
    }

    void CustomLeaderboardManager::Unregister(Models::CustomLeaderboard* customLeaderboard) {
        auto id = customLeaderboard->get_LeaderboardId();
        INFO("Unregistering leaderboard with ID '{}'", id);
        customLeaderboardsById.erase(id);
        OnLeaderboardsChanged();
    }

    void CustomLeaderboardManager::OnLeaderboardsChanged() {
        orderedCustomLeaderboards.clear();
        for (const auto& [key, value] : customLeaderboardsById) {
            orderedCustomLeaderboards.insert(value);
        }

        for (const auto& lb : notifyCustomLeaderboardsChanges) {
            lb->OnLeaderboardsChanged(orderedCustomLeaderboards, customLeaderboardsById);
        }

        if (onLeaderboardsChangedEvent.size() > 0) onLeaderboardsChangedEvent.invoke(orderedCustomLeaderboards, customLeaderboardsById);
    }
}