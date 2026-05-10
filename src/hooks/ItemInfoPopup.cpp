#include <Geode/Geode.hpp>
#include <Geode/modify/ItemInfoPopup.hpp>

using namespace geode::prelude;

class $modify(GDOItemInfoPopup, ItemInfoPopup)
{
    bool init(int p0, UnlockType p1)
    {
        if (!ItemInfoPopup::init(p0, p1))
            return false;

        int type = static_cast<int>(p1);
    
        //  log::info("{}", type);

        if (type >= 900)
        {
            auto player = SimplePlayer::create(0);

            player->updatePlayerFrame(1, static_cast<IconType>(type));
            player->setColor(GameManager::sharedState()->colorForIdx(17));

            auto itemIcon = m_mainLayer->getChildByID("item-icon");
            itemIcon->removeAllChildrenWithCleanup(true);

            player->setPosition(itemIcon->getContentSize() / 2);
            itemIcon->addChild(player);
        }

        return true;
    }

    static gd::string nameForUnlockType(int p0, UnlockType p1)
    {
        switch (static_cast<int>(p1))
        {
        case 900:
            return "Boat";
        case 901:
            return "Drone";
        case 902:
            return "Slider";
        case 903:
            return "Minecart";
        default:
            return ItemInfoPopup::nameForUnlockType(p0, p1);
        }
    }
};
