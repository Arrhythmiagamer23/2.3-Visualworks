#include <Geode/Geode.hpp>
#include <Geode/modify/GJShopLayer.hpp>
#include <Geode/modify/PurchaseItemPopup.hpp>
#include "../layers/OdysseySelectLayer.hpp"
#include "../ui/ShopPromoPopup.hpp"
#include "../utils/IconUtils.hpp"
#include "../utils/Utils.hpp"

using namespace geode::prelude;

class $modify(OdysseyShopLayer, GJShopLayer)
{
    bool init(ShopType p0)
    {
        if (!GJShopLayer::init(ShopType{6}))
            return false;

        FMODAudioEngine::sharedEngine()->playMusic("CarpShop.mp3"_spr, true, 0.1f, 0);

        auto particle = static_cast<CCParticleSystemQuad *>(getChildren()->objectAtIndex(7));
        particle->setStartColor({193, 122, 5, 255});
        particle->setEndColor({255, 122, 0, 0});

        auto winSize = CCDirector::sharedDirector()->getWinSize();
        int rand = (std::rand() % 6) + 1;

        auto wantedPoster = CCSprite::createWithSpriteFrameName(fmt::format("ShopDeco_{:02}_001.png"_spr, rand).c_str());
        wantedPoster->setPosition({(winSize.width / 4) + (std::rand() % 3 * 30), winSize.height / 2 + 70.f});
        wantedPoster->setID("shop-decoration"_spr);
        wantedPoster->setScale(1.333f);
        wantedPoster->setZOrder(-1);
        this->addChild(wantedPoster);

        auto GSM = GameStatsManager::sharedState();

        return true;
    }

    void onBack(CCObject *)
    {
        auto director = CCDirector::sharedDirector();
        auto winSize = director->getWinSize();

        this->retain();
        this->removeFromParentAndCleanup(false);

        auto selectLayer = OdysseySelectLayer::scene(GameManager::sharedState()->getIntGameVariable("1001") - 1);
        director->replaceScene(selectLayer);
        selectLayer->addChild(this, 1000);

        this->release();

        auto moveTo = CCMoveTo::create(0.3f, ccp(0, winSize.height));
        auto easeIn = CCEaseIn::create(moveTo, 2.0f);
        auto callFunc = CCCallFunc::create(this, callfunc_selector(OdysseyShopLayer::removeFromParent));

        auto ccSeq = CCSequence::create(easeIn, callFunc, 0);
        this->runAction(ccSeq);

        setKeyboardEnabled(false);
        setKeypadEnabled(false);
    }
