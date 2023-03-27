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
    class ATMA_API Vec3
    {
    public:
        // default constructor
        Vec3(): x(0), y(0), z(0) {}

        /*
         * MSVC requires this constructor to specify a template
         * while GCC throws an exception since it shades the template
         * from the class definition
         */

#ifdef _WINDOWS
        template<class T>
#endif
        // constructor specifying vector values
        Vec3(T a, T b, T c): x(a), y(b), z(c)
        {
        }

        T x;
        T y;
        T z;
    };

    /**
     * addition of vectors
     * @tparam numeric subtype of the vector
     * @param a first vector
     * @param b second vector
     * @returns resulting composite vector
     */
    template<class T>
    inline Vec3<T> operator+(Vec3<T> a, Vec3<T> b)
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
    inline Vec3<T> operator-(Vec3<T> a, Vec3<T> b)
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
    inline Vec3<T> operator*(Vec3<T> a, T b)
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
    inline T operator*(Vec3<T> a, Vec3<T> b)
    {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
    }

    /**
     * inline cross product for 3D vectors
     * @tparam T numeric subtype of vector
     * @param a first vector
     * @param b second vector
     * @return resulting orthogonal vector
     */
    template<class T>
    inline Vec3<T> cross(Vec3<T> a, Vec3<T> b)
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
    inline bool operator==(Vec3<T> a, Vec3<T> b)
    {
        return std::fabs(a.x - b.x) <= std::numeric_limits<T>::epsilon()
            && std::fabs(a.y - b.y) <= std::numeric_limits<T>::epsilon()
            && std::fabs(a.z - b.z) <= std::numeric_limits<T>::epsilon();
    }

}