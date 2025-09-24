#ifndef ATMA_SERVER
#    include <atomina.hpp>
#    include "Game.hpp"

std::unique_ptr<ATMA::Game> ATMA::CreateGame()
{
    return std::unique_ptr<ATMA::Game>{new GameBenchmark()};
}
#endif
