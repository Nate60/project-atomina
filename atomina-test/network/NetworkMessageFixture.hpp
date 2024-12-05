#pragma once
// conversion to template types causing warning
#include "AtominaTest.hpp"

/**
 * Fixture for testing attribute of the Object Attribute System
 */
class NetworkMessageFixture: public ::testing::Test
{
public:
protected:

};

/**
 * Fixture for testing attribute of the Object Attribute System
 */
template <class T>
class TypedNetworkMessageFixture: public ::testing::Test
{
public:
protected:
    /**
     * Helper function for removing attribute from the context
     * @param l_obj id of the object to remove from
     * @param attr attribute to remove from object
     */
    
    std::pair<unsigned char, std::any> getSomeProperty(unsigned char t)
    {
        auto value =
            std::numeric_limits<T>::max();
        return std::make_pair(t, value);
    }
};

//template<>
//class TypedNetworkMessageFixture<std::string>
//{
//protected:
//    std::pair<unsigned char, std::any> getSomeProperty(unsigned char t)
//    {
//        return std::make_pair(ATMA::NetworkMessageValueType(ATMA::NetworkMessageValueEnum::STRING),"abcdefghijkl");
//    }
//};