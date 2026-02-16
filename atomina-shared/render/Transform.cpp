#include "render/Transform.hpp"
#include "pch.hpp"

namespace ATMA
{
    Transform::Transform(
        const Vec2<float> &l_pos,
        const Vec2<float> &l_size,
        const float &l_rot,
        const Vec2<float> &l_selectPos,
        const Vec2<float> &l_selectSize,
        const Vec2<float> &l_selectAdv
    ):
        m_pos(l_pos),
        m_size(l_size),
        m_rot(l_rot),
        m_selectPos(l_selectPos),
        m_selectSize(l_selectPos),
        m_selectAdv(l_selectAdv)
    {
    }

    Transform::Transform(const Transform &l_other)
    {
        m_pos = l_other.m_pos;
        m_size = l_other.m_size;
        m_rot = l_other.m_rot;
        m_selectPos = l_other.m_selectPos;
        m_selectSize = l_other.m_selectSize;
        m_selectAdv = l_other.m_selectAdv;
    }

    Transform::Transform(Transform &&l_other)
    {
        m_pos = std::move(l_other.m_pos);
        m_size = std::move(l_other.m_size);
        m_rot = std::move(l_other.m_rot);
        m_selectPos = std::move(l_other.m_selectPos);
        m_selectSize = std::move(l_other.m_selectSize);
        m_selectAdv = std::move(l_other.m_selectAdv);
    }

    Transform::~Transform() {}

    void Transform::operator=(const Transform &l_other)
    {
        m_pos = l_other.m_pos;
        m_size = l_other.m_size;
        m_rot = l_other.m_rot;
        m_selectPos = l_other.m_selectPos;
        m_selectSize = l_other.m_selectSize;
        m_selectAdv = l_other.m_selectAdv;
    }

    void Transform::operator=(Transform &&l_other)
    {
        m_pos = std::move(l_other.m_pos);
        m_size = std::move(l_other.m_size);
        m_rot = std::move(l_other.m_rot);
        m_selectPos = std::move(l_other.m_selectPos);
        m_selectSize = std::move(l_other.m_selectSize);
        m_selectAdv = std::move(l_other.m_selectAdv);
    }
}
