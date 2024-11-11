#pragma once
#include <atomina.hpp>
#include <gtest/gtest.h>

/*
 * extension of the Game class from atomina-api
 * used as actual implementation
 */
class ServerTest: public ATMA::Server
{
public:
    ServerTest();
    ~ServerTest();
    virtual void setup(ATMA::ATMAContext &l_ctx) override;
    virtual void update(ATMA::ATMAContext &l_ctx) override;
    virtual void shutdown(ATMA::ATMAContext &l_ctx) override;
};
