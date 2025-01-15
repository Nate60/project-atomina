#pragma once
#include "AtominaTest.hpp"

/**
 * A dummy attribute for testing purposes
 */
class NetworkAttribute: public ATMA::AttrBase
{
public:
    /**
     * Basic constructor
     */
    NetworkAttribute(): AttrBase(0u, "network"){}

    /**
     * Basic deconstructor
     */
    ~NetworkAttribute(){}

    /**
     * friend function for reading out all parameters
     * @param l_stream output stream
     * @param b the attribute of which the parameters will be written
     * @returns stream with attribute member contents appended
     */
    friend std::stringstream &operator>>(std::stringstream &l_stream, AttrBase &b);

    /**
     * Obtains all values for members from a stream
     * @param l_stream input stream containing attribute members
     */
    void readIn(std::stringstream &l_stream){}

    std::unordered_map<unsigned short, ATMA::Props> m_resps{};
    std::optional<unsigned int> m_connId = std::nullopt;
};