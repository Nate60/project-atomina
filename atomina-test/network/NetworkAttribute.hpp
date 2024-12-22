#pragma once
#include "AtominaTest.hpp"

/**
 * A dummy attribute for testing purposes
 */
class TestAttribute: public ATMA::AttrBase
{
public:
    /**
     * Basic constructor
     */
    TestAttribute();

    /**
     * Basic deconstructor
     */
    ~TestAttribute();

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
    void readIn(std::stringstream &l_stream);

    bool flag = false;
};