#pragma once
#include "util/AtominaException.hpp"
#include "math/Vec2.hpp"
#include "math/Vec3.hpp"
#include "math/Mat3.hpp"

namespace ATMA
{

    /**
     * Linear Interpolation between two values, with a given delta
     * @tparam subtype to interpolate
     * @tparam type of ratio parameter
     * @param v0 Starting Boundary of interpolation
     * @param v1 Ending Boundary of interpolation
     * @param t The delta as a ratio of (v-v0)/v1-v0, must be between 0 and 1
     */
    template<class T, class V>
    constexpr inline T lerp(const T &v0, const T &v1, const V &t)
    {
        if(t > 1 || t < 0)
        {
            throw std::invalid_argument("delta must be between 0 and 1");
        }
        return static_cast<T>((1 - t) * v0 + t * v1);
    }

    /**
     * Cubic interpolation between two values with a given delta, used for smoother stepping
     * @tparam subtype to interpolate
     * @tparam type of ratio parameter
     * @param v0 Starting Boundary of interpolation
     * @param v1 Ending Boundary of interpolation
     * @param t The delta as a ratio of (v-v0)/v1-v0, must be between 0 and 1
     */
    template<class T, class V>
    constexpr inline T cubeTerp(const T &a0, const T &a1, const V &w)
    {
        if(w > 1 || w < 0)
            throw std::invalid_argument("delta must be between 0 and 1");
        return static_cast<T>((a1 - a0) * (3 - w * 2) * w * w + a0);
    }

    /**
     * Used to generate perlin noise at a specific location on a gradient
     * @tparam subtype to interpolate
     * @tparam type of ratio parameter
     * @param gradient: Array of 4 directional vectors that define the gradient around the point
     * @param interpolate: interpolation function to interpolate values in the gradient
     * @param l_x: x coordinate point to get the noise at
     * @param l_y: y coordinate point to get the noise at
     */
    template<class T, class V>
    T perlin(const Vec2<T> l_gradient[4],const std::function<T(const T &, const T &, const V &)> l_lerp, const T &l_x, const T &l_y)
    {
        T a0 = static_cast<T>(std::floor(l_x));
        T a1 = a0 + 1;
        T b0 = static_cast<T>(std::floor(l_y));
        T b1 = b0 + 1;

        V dx = static_cast<V>(l_x - a0);
        V dy = static_cast<V>(l_y - b0);

        T temp1, temp2, inter1, inter2;

        Vec2<T> distanceVector{static_cast<T>(dx), static_cast<T>(dy)};
        temp1 = l_gradient[0] * distanceVector;

        distanceVector = Vec2<T>(l_x - a1, static_cast<T>(dy));
        temp2 = l_gradient[1] * distanceVector;
        inter1 = static_cast<T>(l_lerp(temp1, temp2, dx));

        distanceVector = Vec2<T>(static_cast<T>(dx), l_y - b1);
        temp1 = l_gradient[2] * distanceVector;

        distanceVector = Vec2<T>(l_x - a1, l_y - b1);
        temp2 = l_gradient[3] * distanceVector;
        inter2 = static_cast<T>(l_lerp(temp1, temp2, dx));

        return static_cast<T>(l_lerp(inter1, inter2, dy));
    }

    /**
     * @brief factory function for identity matrix
     * @tparam T subtype of matrix
     * @return identity matrix
     */
    template<class T>
    constexpr inline Mat3<T> identityMatrix()
    {
        return {
            {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}
        };
    }

    /**
     * @brief factory function for scaling matrix
     * @tparam T subtype of matrix
     * @return scaling matrix
     */
    template<class T>
    constexpr inline Mat3<T> scalingMatrix(const T &l_x, const T &l_y)
    {
        return {
            {{l_x, 0, 0}, {0, l_y, 0}, {0, 0, 1}}
        };
    }

    /**
     * @brief factory function for translation matrix
     * @tparam T subtype of matrix
     * @return translation matrix
     */
    template<class T>
    constexpr inline Mat3<T> translationMatrix(const T &l_x, const T &l_y)
    {
        return {
            {{1, 0, l_x}, {0, 1, l_y}, {0, 0, 1}}
        };
    }

    /**
     * @brief factory function for rotation
     * @tparam T subtype of matrix
     * @return rotation matrix
     */
    template<class T>
    constexpr inline Mat3<T> rotationMatrix(const T &l_deg)
    {
        double rad = (M_PI * l_deg) / 180.0;
        T cosVal = static_cast<T>(cos(rad));
        T sinVal = static_cast<T>(sin(rad));
        Mat3<T> mat{
            {{cosVal, -1 * sinVal, 0}, {sinVal, cosVal, 0}, {0, 0, 1}}
        };
        return mat;
    }

    /**
    * @brief given two points, find the closest point between those
    * two points to the given point
    * @tparam T subtype of Vec2
    * @param l_a first point of line
    * @param l_b second point of line
    * @param l_point point to align to
    * @returns point between two points closest to the line
    */
    template<class T>
    constexpr inline Vec2<T> lerpClosest(const Vec2<T> &l_a, const Vec2<T> &l_b, const Vec2<T> &l_point)
    {
        Vec2<T> line = l_b - l_a;
        if(line * line == 0)
            return l_a;
        T delta = ((l_point - l_a) * line) / (line * line);
        return l_a + (line * std::clamp<T>(delta, 0, 1));
    }


}
