#include "pch.hpp"
#include "AttrGraphic.hpp"

namespace ATMA
{

    AttrGraphic::AttrGraphic(): AttrBase(AttrType(ATMA::Attribute::Graphic), "Graphic") {}

    AttrGraphic::~AttrGraphic() {}

    void AttrGraphic::updateScreenPosition(const float &l_x, const float &l_y)
    {
        m_sprite.setPosition(sf::Vector2f{l_x, l_y});
    }

    void AttrGraphic::draw(sf::RenderTarget &l_target, const sf::RenderStates &l_states) const
    {
        l_target.draw(m_sprite, l_states);
    }

    void AttrGraphic::readIn(std::stringstream &l_stream) {}

}
