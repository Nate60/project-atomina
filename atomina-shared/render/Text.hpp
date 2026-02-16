#pragma once
#include "math/Vec2.hpp"
#include "pch.hpp"
#include "render/Renderable.hpp"
#include "render/Transform.hpp"
#include "util/ATConst.hpp"

namespace ATMA
{
    struct TextData
    {
        std::string m_text{};
        Vec2<float> m_pos{0.f, 0.f};
        Vec2<float> m_size{1.f, 1.f};
        Vec2<float> m_spacing{1.f, 1.f};
    };

    class Text: public Renderable
    {
    public:
        Text();
        Text(const TextData &l_data);
        virtual ~Text();
        const TextData &getData() const;
        void setText(const std::string &l_text);
        void setPos(const Vec2<float> &l_pos);
        void setSize(const Vec2<float> &l_size);
    protected:
        static void generateTransforms(const TextData &l_data, TransformContainer &l_transforms);
        TextData m_data;
    };
}
