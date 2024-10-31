#include "pch.hpp"
#include "AttrSprite.hpp"

namespace ATMA
{

    AttrSprite::AttrSprite(): AttrBase(AttrType(Attribute::Sprite), "Sprite") {}

    AttrSprite::~AttrSprite() {}

    void AttrSprite::readIn(std::stringstream &l_stream) {}

}