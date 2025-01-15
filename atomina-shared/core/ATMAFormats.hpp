#pragma once
#include "pch.hpp"

namespace ATMA
{

    /**
    * Conversion function to convert shared_ptr to its inner type for logging
    * purposes
    * @template inner type (deduced)
    * @param os logging stream
    * @param a smart pointer object to be logged
    * @returns stream with object
    */
    template<class T>
    inline std::ostream &operator<<(std::ostream &os, const std::shared_ptr<T> a)
    {
        return os << (*a);
    }

    /**
    * Conversion function to convert optional to its inner type for logging
    * purposes
    * @template inner type (deduced)
    * @param os logging stream
    * @param a optional object to be logged
    * @returns stream with object
    */
    template<class T>
    inline std::ostream &operator<<(std::ostream &os, const std::optional<T> a)
    {
        if(a.has_value)
            return os << a.value();
        return os << "[NONE]";
    }

}
