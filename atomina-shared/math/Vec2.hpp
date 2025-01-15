#pragma once
#include "pch.hpp"
#include "core/api.hpp"

namespace ATMA
{

    /**
     * @brief 2 dimensional vector for math applications
     * @tparam T numeric subtype of the vector
     */
    template<class T>
    struct Vec2
    {
        T x{0};
        T y{0};
    };

    /**
     * addition of vectors
     * @tparam numeric subtype of the vector
     * @param a first vector
     * @param b second vector
     * @returns resulting composite vector
     */
    template<class T>
    constexpr inline Vec2<T> operator+(Vec2<T> a, Vec2<T> b)
    {
        return {a.x + b.x, a.y + b.y};
    }

    /**
     * subtraction of vectors
     * @tparam numeric subtype of the vector
     * @param a first vector
     * @param b second vector
     * @returns resulting composite vector
     */
    template<class T>
    constexpr inline Vec2<T> operator-(Vec2<T> a, Vec2<T> b)
    {
        return {a.x - b.x, a.y - b.y};
    }

    /**
     * scalar multiplication
     * @tparam numeric subtype of the vector
     * @param a vector
     * @param b scalar
     * @returns resulting magnified vector
     */
    template<class T>
    constexpr inline Vec2<T> operator*(Vec2<T> a, T b)
    {
        return {(a.x * b), (a.y * b)};
    }

    /**
     * scalar division
     * @tparam numeric subtype of the vector
     * @param a vector
     * @param b scalar
     * @returns resulting magnified vector
     */
    template<class T>
    constexpr inline Vec2<T> operator/(Vec2<T> a, T b)
    {
        return {(a.x / b), (a.y / b)};
    }

    /**
     * inline dot product function for vectors
     * @tparam numeric subtype of the vector
     * @param a first vector
     * @param b second vector
     * @returns resulting scalar value
     */
    template<class T>
    constexpr inline T operator*(Vec2<T> a, Vec2<T> b)
    {
        return (a.x * b.x) + (a.y * b.y);
    }

    /**
     * inline comparision operator
     * @tparam numeric subtype of the vector
     * @param a first vector
     * @param b second vector
     * @returns resulting boolean
     */
    template<class T>
    constexpr inline bool operator==(Vec2<T> a, Vec2<T> b)
    {
        return std::fabs(a.x - b.x) <= std::numeric_limits<T>::epsilon()
            && std::fabs(a.y - b.y) <= std::numeric_limits<T>::epsilon();
    }

    template<class T>
    constexpr inline Vec2<T> normalize(Vec2<T> l_vector)
    {
        T dist = static_cast<T>(std::sqrt(l_vector * l_vector));
        if(dist == 0) // 0 vector cannot be normalized
            return l_vector;
        return Vec2<T>{l_vector.x / dist, l_vector.y / dist};
    }

}