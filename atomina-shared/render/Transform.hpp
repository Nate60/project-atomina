#pragma once
#include "pch.hpp"
#include "math/Vec2.hpp"

namespace ATMA
{
    class Transform
    {
    public:
        Vec2<float> m_pos{0.f, 0.f};
        Vec2<float> m_size{1.f, 1.f};
        float m_rot{0.f};
        Vec2<float> m_selectPos{0.f, 0.f};
        Vec2<float> m_selectSize{1.f, 1.f};
        Vec2<float> m_selectAdv{0.f, 0.f};
        Transform(
            const Vec2<float> &l_pos = Vec2<float>{0.f, 0.f},
            const Vec2<float> &l_size = Vec2<float>{1.f, 1.f},
            const float &l_rot = float{0.f},
            const Vec2<float> &l_selectPos = Vec2<float>{0.f, 0.f},
            const Vec2<float> &l_selectSize = Vec2<float>{1.f, 1.f},
            const Vec2<float> &l_selectAdv = Vec2<float>{0.f, 0.f}
        );

        Transform(const Transform &l_other);

        Transform(Transform &&l_other);

        virtual ~Transform();

        void operator=(const Transform &l_other);

        void operator=(Transform &&l_other);
    };
}
