#pragma once
#include "pch.hpp"
#include "math/Vec2.hpp"
#include "math/Mat3.hpp"
#include "math/MathFuncs.hpp"

namespace ATMA
{
    /**
    * aggregate for storing the matrix that defines the camera for rendering
    */
    class GLCamera
    {
    public:
        
        //constructor
        GLCamera(
            const Vec2<float> &l_pos = Vec2<float>{0.f, 0.f},
            const Vec2<float> &l_region = Vec2<float>{1.f, 1.f},
            const float &l_rot = 0.f
        );

        /**
        * gets the projection matrix of the camera according to its attributes
        * @return 3x3 Matrix projection for camera
        */
        const Mat3<float> &getProjectionMatrix() const;
    protected:
        Vec2<float> m_pos;
        Vec2<float> m_region;
        float m_rot;
        Mat3<float> m_proj;
    };
}