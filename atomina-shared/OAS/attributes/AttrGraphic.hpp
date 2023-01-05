#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "OAS/AttrBase.hpp"

namespace ATMA
{

    /**
     * Attribute that has the object's sprite and graphic members
     */
    class ATMA_API AttrGraphic: public AttrBase, sf::Drawable
    {
    public:

        //default constructor
        AttrGraphic();

        //deconstructor
        ~AttrGraphic();

        /**
         * Moves the sprite position to the given position coords
         * @param l_x x coord of the new position
         * @param l_y y coord of the new position
         */
        virtual void updateScreenPosition(const float &l_x, const float &l_y);
        
        /**
         * draws the object's sprite to the render target
         * @param l_target the target to render the sprite to
         * @param l_states state set for the render target 
         */
        virtual void draw(sf::RenderTarget &l_target, const sf::RenderStates &l_states)
            const override;

        /**
         * fill attribute members with data contained within a string stream
         * @param l_stream string stream containing data of the attribute members
         */
        virtual void readIn(std::stringstream &l_stream) override;

        sf::Sprite m_sprite{};
    };

}