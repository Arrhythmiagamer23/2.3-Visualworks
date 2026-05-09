#pragma once
using namespace geode::prelude;

namespace Odyssey
{
    void patch(int, geode::ByteVector const &);
    std::vector<unsigned char> intToBytes(int);
};
