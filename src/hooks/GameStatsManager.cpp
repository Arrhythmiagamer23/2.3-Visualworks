#include <Geode/Geode.hpp>
#include <Geode/modify/GameStatsManager.hpp>
#include "../utils/IconUtils.hpp"

using namespace geode::prelude;

class $modify(OdysseyGameStatsManager, GameStatsManager)
{
    bool isItemUnlocked(UnlockType type, int ID)
    {
        //  Practice Music Unlocker
        if (type == UnlockType::GJItem && ID == 17)
            return true;

        return GameStatsManager::isItemUnlocked(type, ID);
    }

    int getItemUnlockState(int p0, UnlockType p1)
    {
        //  El icono no es custom
        if (!IconUtils::isIconCustom(p0, GameManager::sharedState()->unlockTypeToIconType(static_cast<int>(p1))))
            return 4;

        //  No tiene achievement
        if (!AchievementManager::sharedState()->achievementForUnlock(p0, p1).empty())
            return 1;

        //  Icono aun no ha salido
        //  if (IconUtils::isIconUpcoming(p0, GameManager::sharedState()->unlockTypeToIconType(static_cast<int>(p1))))
        //  return 6;

        if (IconUtils::isIconSpecial(p0, GameManager::sharedState()->unlockTypeToIconType(static_cast<int>(p1))))
            return 7;

        //  Icono de tienda
        return 5;
    }
};
