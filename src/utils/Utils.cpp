#include "Utils.hpp"

//  Adds corners to the "Level Popups"
void Odyssey::addCorners(CCLayer *layer, const char *cornerSprite, float offset)
{
    auto m_cornerBL = CCSprite::createWithSpriteFrameName(cornerSprite);
    m_cornerBL->setAnchorPoint({0, 0});
    m_cornerBL->setPosition({0 - offset, 0 - offset});
    m_cornerBL->setID("corner-bl"_spr);

    auto m_cornerBR = CCSprite::createWithSpriteFrameName(cornerSprite);
    m_cornerBR->setPosition({layer->getContentWidth() + offset, 0 - offset});
    m_cornerBR->setAnchorPoint({1, 0});
    m_cornerBR->setFlipX(true);
    m_cornerBR->setID("corner-br"_spr);

    auto m_cornerTL = CCSprite::createWithSpriteFrameName(cornerSprite);
    m_cornerTL->setAnchorPoint({0, 1});
    m_cornerTL->setPosition({0 - offset, layer->getContentHeight() + offset});
    m_cornerTL->setFlipY(true);
    m_cornerTL->setID("corner-tl"_spr);

    auto m_cornerTR = CCSprite::createWithSpriteFrameName(cornerSprite);
    m_cornerTR->setPosition({layer->getContentWidth() + offset, layer->getContentHeight() + offset});
    m_cornerTR->setAnchorPoint({1, 1});
    m_cornerTR->setFlipX(true);
    m_cornerTR->setFlipY(true);
    m_cornerTR->setID("corner-tr"_spr);

    layer->addChild(m_cornerBL);
    layer->addChild(m_cornerBR);
    layer->addChild(m_cornerTL);
    layer->addChild(m_cornerTR);
};

void Odyssey::patch(int address, geode::ByteVector const &data)
{
    geode::Mod::get()->patch(reinterpret_cast<void *>(geode::base::get() + address), data).unwrap();
}

std::vector<unsigned char> Odyssey::intToBytes(int value)
{
    std::vector<unsigned char> result;
    result.push_back(value & 0x000000ff);
    result.push_back((value & 0x0000ff00) >> 8);
    result.push_back((value & 0x00ff0000) >> 16);
    result.push_back((value & 0xff000000) >> 24);
    return result;
}
