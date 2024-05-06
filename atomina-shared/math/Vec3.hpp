#pragma once
#include "pch.hpp"
#include "core/api.hpp"

namespace ATMA
{

    /**
     * @brief 3 dimensional vector for math applications
     * @tparam T numeric subtype of the vector
     */
    template<class T>
    struct Vec3
    {
        T x{0};
        T y{0};
        T z{0};
    };

    /**
     * addition of vectors
     * @tparam numeric subtype of the vector
     * @param a first vector
     * @param b second vector
     * @returns resulting composite vector
     */
    template<class T>
    constexpr inline Vec3<T> operator+(Vec3<T> a, Vec3<T> b)
    {
        return {a.x + b.x, a.y + b.y, a.z + b.z};
    }

    /**
     * subtraction of vectors
     * @tparam numeric subtype of the vector
     * @param a first vector
     * @param b second vector
     * @returns resulting composite vector
     */
    template<class T>
    constexpr inline Vec3<T> operator-(Vec3<T> a, Vec3<T> b)
    {
        return {a.x - b.x, a.y - b.y, a.z - b.z};
    }

    /**
     * scalar multiplication
     * @tparam numeric subtype of the vector
     * @param a vector
     * @param b scalar
     * @returns resulting magnified vector
     */
    template<class T>
    constexpr inline Vec3<T> operator*(Vec3<T> a, T b)
    {
        return {(a.x * b), (a.y * b), (a.z * b)};
    }

    /**
     * inline dot product function for vectors
     * @tparam numeric subtype of the vector
     * @param a first vector
     * @param b second vector
     * @returns resulting scalar value
     */
    template<class T>
    constexpr inline T operator*(Vec3<T> a, Vec3<T> b)
    {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
    }

    /**
     * scalar division
     * @tparam numeric subtype of the vector
     * @param a vector
     * @param b scalar
     * @returns resulting magnified vector
     */
    template<class T>
    constexpr inline Vec3<T> operator/(Vec3<T> a, T b)
    {
        return {(a.x / b), (a.y / b), (a.z / b)};
    }

    /**
     * inline cross product for 3D vectors
     * @tparam T numeric subtype of vector
     * @param a first vector
     * @param b second vector
     * @return resulting orthogonal vector
     */
    template<class T>
    constexpr inline Vec3<T> cross(Vec3<T> a, Vec3<T> b)
    {
        return {(a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z), (a.x * b.y) - (a.y * b.x)};
    }

    /**
     * inline comparision operator
     * @tparam numeric subtype of the vector
     * @param a first vector
     * @param b second vector
     * @returns resulting boolean
     */
    template<class T>
    constexpr inline bool operator==(Vec3<T> a, Vec3<T> b)
    {
        return std::fabs(a.x - b.x) <= std::numeric_limits<T>::epsilon()
            && std::fabs(a.y - b.y) <= std::numeric_limits<T>::epsilon()
            && std::fabs(a.z - b.z) <= std::numeric_limits<T>::epsilon();
    }

    template<class T>
    constexpr inline Vec3<T> normalize(Vec3<T> l_vector)
    {
        T dist = static_cast<T>(std::sqrt(l_vector * l_vector));
        if(dist == 0) //0 vector cannot be normalized
            return l_vector;
        return Vec3<T>{l_vector.x / dist, l_vector.y / dist, l_vector.z / dist};
    }

}