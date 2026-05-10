#include <Geode/Geode.hpp>
#include <Geode/modify/ItemInfoPopup.hpp>
#include "../utils/IconUtils.hpp"

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

        if (GameStatsManager::sharedState()->getItemUnlockState(p0, p1) != 1)
        {
            std::string iconName = nameForUnlockType(p0, p1);

            //  Default Icons
            if ((p1 == UnlockType::Cube && p0 <= 4) || p0 == 1 || ((p1 == UnlockType::Col1 || p1 == UnlockType::Col2) && p0 <= 3))
            {
                descriptionString = fmt::format("This <cg>{}</c> is <cl>unlocked</c> by default.", iconName);
                titleString = "Default";
            }
        }
        else
        {
            if (IconUtils::isIconSecret(p0, GameManager::sharedState()->unlockTypeToIconType(static_cast<int>(p1))))
            {
                if (auto descriptionArea = static_cast<TextArea *>(m_mainLayer->getChildByID("description-area")))
                {
                    std::string iconName = nameForUnlockType(p0, p1);
                    std::string descriptionString = fmt::format("A <cy>secret</c> is required to <cl>unlock</c> this <cg>{}</c>!", iconName);
                    descriptionArea->setString(descriptionString);
                }
            }
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
