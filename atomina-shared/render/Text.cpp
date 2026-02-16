#include "Text.hpp"
#include "render/Transform.hpp"

namespace ATMA
{
    void Text::generateTransforms(const TextData &l_data, TransformContainer &l_transforms)
    {
        l_transforms.clear();
        float xAdv = 0.f;
        for(auto itr = l_data.m_text.begin(); itr != l_data.m_text.end(); itr++)
        {
            Transform tt{};
            // select character
            tt.m_selectSize = Vec2<float>{32.f, 32.f};
            int row = *itr % ATConst::FONT_CHARS_PER_ROW;
            int column = (*itr / ATConst::FONT_CHARS_PER_ROW);
            tt.m_selectPos = Vec2<float>{row * 32.f, column * 32.f};
            // assume origin is top left
            tt.m_pos = Vec2<float>{l_data.m_pos.x + xAdv, l_data.m_pos.y};
            tt.m_size = l_data.m_size;
            l_transforms.emplace_back(std::make_pair(nullptr, tt));
            xAdv += l_data.m_spacing.x;
        }
    }

    Text::Text(): Renderable()
    {
        m_data = TextData{};
        Text::generateTransforms(m_data, *this);
    }

    Text::Text(const TextData &l_data): Renderable(), m_data(l_data)
    {
        Text::generateTransforms(m_data, *this);
    }

    Text::~Text() {}

    void Text::setText(const std::string &l_text)
    {
        m_data.m_text = l_text;
        Text::generateTransforms(m_data, *this);
    }

    void Text::setPos(const Vec2<float> &l_pos)
    {
        m_data.m_pos = l_pos;
        Text::generateTransforms(m_data, *this);
    }

    void Text::setSize(const Vec2<float> &l_size)
    {
        m_data.m_size = l_size;
        Text::generateTransforms(m_data, *this);
    }

    const TextData &Text::getData() const
    {
        return m_data;
    }
}
