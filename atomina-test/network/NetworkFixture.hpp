#pragma once
// conversion to template types causing warning
#include "AtominaTest.hpp"

class NetworkFixture: public ::testing::Test
{
protected:
    std::shared_ptr<ATMA::Socket> socket = nullptr;
    std::shared_ptr<ATMA::SocketListener> listener;

    const unsigned short m_port = 8899;

    ATMA::URL m_address{"127.0.0.1"};

    void SetUp() override
    {
        listener = ATMA::SocketListener::makeSocketListener(m_port);
    }

    void TearDown() override
    {
        socket = nullptr;
        listener = nullptr;
    }
};
