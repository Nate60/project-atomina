#include "math/MathFuncs.hpp"
#include "pch.hpp"
#include "Camera.hpp"
#include "util/Log.hpp"

namespace ATMA
{

    Camera::Camera(const Vec2<float> &l_pos, const Vec2<float> &l_region, const float &l_rot)
    {
        // m_proj = translationMatrix(l_pos.x, l_pos.y) * scalingMatrix(l_region.x, l_region.y) * rotationMatrix(l_rot);
        m_proj = orthogonalMatrix<float>(l_pos.x, l_pos.y, l_region.x, l_region.y);
        m_pos = l_pos;
        m_region = l_region;
        m_rot = l_rot;
    }

    const Mat3<float> &Camera::getProjectionMatrix() const
    {
        return m_proj;
    }

}
