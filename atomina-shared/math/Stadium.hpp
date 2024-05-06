#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "Vec2.hpp"
#include "Vec3.hpp"
#include "Mat3.hpp"
#include "math/MathFuncs.hpp"
#include "util/Log.hpp"

namespace ATMA
{
    //NOTE: Templated classes should not be exported
    /**
     * @brief 2 dimensional polygon that is defined by two semi circles
     * joined a by a rectangle. The center points of the semi circles are
     * defined by the vectors a and b and the semi circle's radii are defined
     * by r. The inner rectangle is constrained by r and the distance between
     * a and b
     * @tparam the numeric subtype of the parameters of the stadium
     */
    template<class T>
    struct Stadium
    {
        Vec2<T> a{}, b{};
        T r{};

        /**
         * @brief move the base of the stadium and perserve the stadium's
         * rotation and shape
         * @param l_pos the new position to move to
         */
        void setBase(const Vec2<T> &l_pos)
        {
            Vec2<T> offsetB = b - a;                  // from A
            Vec2<T> offsetA = normalize(offsetB) * r; // from object base
            a = l_pos + offsetA;
            b = a + offsetB;
        }

        /**
         * @brief get the point in space that corresponds to the base of
         * the stadium, that being the point on the principal axis that touches
         * the edge of semi-circle A
         * @returns the position vector of the base of the stadium
         */
        Vec2<T> getBase()
        {
            Vec2<T> offsetA = a - b; // from B
            return (normalize(offsetA) * r) + a;
        }

        /**
         * @brief sets the rotation of the stadium relative to its
         * base
         * @param l_rot the angle in degrees to set the rotation to
         */
        void setRotation(T l_rot)
        {
            // since rotating a vector using a rotation matrix rotates it
            // around the origin we need to first make the positional vectors
            // a and b relative to the stadium's base
            Vec2<T> base = getBase();
            Vec2<T> offsetA = a - base;
            Vec2<T> offsetB = b - base;
            Vec3<T> rotA = rotationMatrix(l_rot) * Vec3<T>{offsetA.x, offsetA.y, 1};
            Vec3<T> rotB = rotationMatrix(l_rot) * Vec3<T>{offsetB.x, offsetB.y, 1};
            // need to re-make vectors relative to origin now
            a = Vec2<T>{rotA.x, rotA.y} + base;
            b = Vec2<T>{rotB.x, rotB.y} + base;
        }

        /**
         * @brief the stadiums rotation relative to its principal axis
         * or its base
         * @returns rotation in degrees
         */
        T getRotation()
        {
            long double rad = std::asin(normalize(b - a).y);
            return static_cast<T>((rad * 180.0) / M_PI);
        }
    };

    /**
     * inline comparision operator
     * @tparam numeric subtype of the stadium
     * @param a first stadium
     * @param b second stadium
     * @returns resulting boolean
     */
    template<class T>
    constexpr inline bool operator==(Stadium<T> a, Stadium<T> b)
    {
        return a.a == b.a && a.b == b.b
            && std::fabs(a.r - b.r) <= std::numeric_limits<T>::epsilon();
    }

    /**
     * @brief for a given pair of stadiums will check if they intersect and will give
     * the intersection normal for determining the direction and magnitude at which to move
     * to undo the intersection
     * @tparam numeric subtype of the stadiums and underlying vectors
     * @param l_a the first stadium
     * @param l_b the second stadium
     * @param l_result the vector reference which will contain the resulting intersection normal
     * if one exists
     * @returns if an intersection exists
     */
    template<class T>
    bool getCollideVector(const Stadium<T> &l_a, const Stadium<T> &l_b, Vec2<T> &l_result)
    {
        Vec2<T> principalA = normalize(l_a.b - l_a.a);
        Vec2<T> principalB = normalize(l_b.b - l_b.a);

        Vec2<T> v0 = l_b.a - l_a.a;
        Vec2<T> v1 = l_b.b - l_a.a;
        Vec2<T> v2 = l_b.a - l_a.b;
        Vec2<T> v3 = l_b.b - l_a.b;

        T d0 = v0 * v0;
        T d1 = v1 * v1;
        T d2 = v2 * v2;
        T d3 = v3 * v3;

        Vec2<T> bestA{};
        if(d2 < d0 || d2 < d1 || d3 < d0 || d3 < d1)
        {
            bestA = l_a.b;
        }
        else
        {
            bestA = l_a.a;
        }

        Vec2<T> bestB = lerpClosest(l_b.a, l_b.b, bestA);
        bestA = lerpClosest(l_a.a, l_a.b, bestB);
        Vec2<T> collideVector = bestA - bestB;
        T collideVectorLength = static_cast<T>(std::sqrt(collideVector * collideVector));
        T intersectionLength = (l_a.r + l_b.r) - collideVectorLength;
        if(intersectionLength <= 0)
        {
            return false;
        }
        else
        {
            l_result = (collideVector / intersectionLength);
            return true;
        }
    }

}