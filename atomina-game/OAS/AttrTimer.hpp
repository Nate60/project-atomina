#pragma once
#include <atomina.hpp>
#include "../GameEnums.hpp"

class AttrTimer: public ATMA::AttrBase
{
public:
    AttrTimer() : AttrBase(GameAttributeType(GameAttributeEnum::TIMER), "Timer")
    {
    }

    virtual ~AttrTimer()
    {
    }

    /**
     * fill attribute members with data contained within a string stream
     * @param l_stream string stream containing data of the attribute members
     */
    void readIn(std::stringstream &l_stream) override {}

    ATMA::StopWatch m_clock{};
    long long m_amount{};
    bool m_elapsed{};


};