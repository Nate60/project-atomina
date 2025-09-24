#ifdef ATMA_SERVER
#    include <atomina.hpp>
#    include "Server.hpp"

std::unique_ptr<ATMA::Server> ATMA::CreateServer()
{
    return std::unique_ptr<ATMA::Server>{new ServerBenchmark()};
}
#endif
