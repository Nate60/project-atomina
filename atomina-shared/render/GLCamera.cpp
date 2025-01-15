#include "pch.hpp"
#include "GLCamera.hpp"
#include "util/Log.hpp"

namespace ATMA
{

    GLCamera::GLCamera(const Vec2<float> &l_pos, const Vec2<float> &l_region, const float &l_rot)
    {
        m_proj = translationMatrix(l_pos.x, l_pos.y) * scalingMatrix(l_region.x, l_region.y) * rotationMatrix(l_rot);
        m_pos = l_pos;
        m_region = l_region;
        m_rot = l_rot;
    }

    const Mat3<float> &GLCamera::getProjectionMatrix() const
    {
        return m_proj;
    }

}