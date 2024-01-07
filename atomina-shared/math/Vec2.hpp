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
    class ATMA_API Vec2
    {
    public:
        // default constructor
        Vec2(): x(0), y(0) {}

        /*
         * MSVC requires this constructor to specify a template
         * while GCC throws an exception since it shades the template
         * from the class definition
         */

#ifdef _WINDOWS
        template<class T>
#endif
        // constructor specifying vector values
        Vec2(T a, T b): x(a), y(b)
        {
        }

        T x;
        T y;
    };

    /**
     * addition of vectors
     * @tparam numeric subtype of the vector
     * @param a first vector
     * @param b second vector
     * @returns resulting composite vector
     */
    template<class T>
    inline Vec2<T> operator+(Vec2<T> a, Vec2<T> b)
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
    inline Vec2<T> operator-(Vec2<T> a, Vec2<T> b)
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
    inline Vec2<T> operator*(Vec2<T> a, T b)
    {
        return {(a.x * b), (a.y * b)};
    }

    /**
     * inline dot product function for vectors
     * @tparam numeric subtype of the vector
     * @param a first vector
     * @param b second vector
     * @returns resulting scalar value
     */
    template<class T>
    inline T operator*(Vec2<T> a, Vec2<T> b)
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
    inline bool operator==(Vec2<T> a, Vec2<T> b)
    {
        return std::fabs(a.x - b.x) <= std::numeric_limits<T>::epsilon()
            && std::fabs(a.y - b.y) <= std::numeric_limits<T>::epsilon();
    }

}