#include "../../pch.hpp"
#include "AttrDrawable.hpp"

namespace ATMA
{

	AttrDrawable::AttrDrawable(): AttrBase(static_cast<AttributeType>(ATMA::Attribute::Drawable)), m_sheet(getWorkingDirectory() + "..\\res\\shaggysheet.png")
	{
		std::shared_ptr<AnimIdle> idle{new AnimIdle{ "shaggy", 64, 64, 0, 1}};
		m_sheet.addAnimation(idle);
	}

	AttrDrawable::~AttrDrawable()
	{}

	void AttrDrawable::updateScreenPosition(const float &l_x, const float &l_y)
	{
		m_sheet.positionAnimation("shaggy", l_x, l_y);

	}

	void AttrDrawable::draw(sf::RenderTarget &l_target)
	{
		m_sheet.update();
		m_sheet.draw(l_target);
	}

	void AttrDrawable::readIn(std::stringstream &l_stream)
	{}

}

