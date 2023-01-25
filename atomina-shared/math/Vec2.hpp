#pragma once
#include "pch.hpp"
#include "core/api.hpp"

namespace ATMA
{

	template<class T>
	class ATMA_API Vec2
    {
    public:
        Vec2() :x(0), y(0) 
        {
        }

#ifdef _WINDOWS
        template<class T>
#endif
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
     * @tparam numeric subtype of the scalar
     * @param a vector
     * @param b scalar
     * @returns resulting magnified vector
     */
    template<class T>
    inline Vec2<T> operator*(Vec2<T> a, T b)
    {
        return {(a.x * b), (a.y * b)};
    }

}