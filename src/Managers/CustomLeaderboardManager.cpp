#include "Managers/CustomLeaderboardManager.hpp"
#include "Models/CustomLeaderboard.hpp"

namespace LeaderboardCore::Managers {
    std::unordered_set<Interfaces::INotifyLeaderboardChange*> CustomLeaderboardManager::notifyCustomLeaderboardsChanges;
    std::unordered_map<std::string, Models::CustomLeaderboard*> CustomLeaderboardManager::customLeaderboardsById;
    UnorderedEventCallback<const std::set<Models::CustomLeaderboard*>&, const std::unordered_map<std::string, Models::CustomLeaderboard*>&> CustomLeaderboardManager::onLeaderboardsChangedEvent;

    void CustomLeaderboardManager::Register(Models::CustomLeaderboard* customLeaderboard, const ModInfo& modInfo) {
        if (!customLeaderboardsById.contains(customLeaderboard->get_LeaderboardId())) {
            customLeaderboardsById[customLeaderboard->get_LeaderboardId()] = customLeaderboard;
            OnLeaderboardsChanged();
        }
    }

    void CustomLeaderboardManager::Unregister(Models::CustomLeaderboard* customLeaderboard) {
        customLeaderboardsById.erase(customLeaderboard->get_LeaderboardId());
        OnLeaderboardsChanged();
    }

    void CustomLeaderboardManager::OnLeaderboardsChanged() {
        std::set<LeaderboardCore::Models::CustomLeaderboard *> values;
        for (const auto& [key, value] : customLeaderboardsById) {
            values.insert(value);
        }

        for (const auto& lb : notifyCustomLeaderboardsChanges) {
            lb->OnLeaderboardsChanged(values, customLeaderboardsById);
        }

        if (onLeaderboardsChangedEvent.size() > 0) onLeaderboardsChangedEvent.invoke(values, customLeaderboardsById);
    }
}