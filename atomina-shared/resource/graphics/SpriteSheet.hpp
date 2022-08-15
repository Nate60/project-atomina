#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "AnimBase.hpp"
#include "util/Log.hpp"
#include "util/ATConst.hpp"
#include "resource/Resource.hpp"

namespace ATMA
{
    class ATMA_API SpriteSheet: public Resource
    {
    public:
        SpriteSheet();
        SpriteSheet(const std::string &l_filename);

        void updateSprite(const std::unique_ptr<AnimBase> &l_anim, sf::Sprite &l_sprite);
    private:
        sf::Texture m_sheet;
    };

    inline bool operator==(const SpriteSheet &a, const SpriteSheet &b);

}