#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "AnimBase.hpp"
#include "util/Log.hpp"
#include "util/ATConst.hpp"
#include "resource/Resource.hpp"

namespace ATMA
{
    /**
     * Sprite sheet implementation of resource, contains one image file
     * and sprites can point to subsections of it
     */
    class ATMA_API SpriteSheet: public Resource
    {
    public:
        
        //constructor specifying name
        SpriteSheet(const std::string &l_name);

        //construction specifying name and filename
        SpriteSheet(const std::string &l_name, const std::string &l_filename);

        //deconstructor
        ~SpriteSheet();

        /**
         * updates the given sprite to point to the subsection described by the given
         * animation
         * @param l_anim animation specifying where the sprite should be
         * @param l_sprite reference of the subsection the sprite sheet 
         */
        void updateSprite(const std::unique_ptr<AnimBase> &l_anim, sf::Sprite &l_sprite);
    private:
        sf::Texture m_sheet;
    };

    //equality operator
    inline bool operator==(const SpriteSheet &a, const SpriteSheet &b);

}