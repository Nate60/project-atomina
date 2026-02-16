#include <atomina.hpp>

/*
 * extension of the Game class from atomina-api
 * used as actual implementation
 */
class ServerBenchmark: public ATMA::Server
{
public:
    std::shared_ptr<ATMA::AppWindow> m_win;

    // default constructor
    ServerBenchmark() {}

    // deconstructor
    ~ServerBenchmark() {}

    /**
     * real implementation of the game apps setup function to house the setup
     */
    virtual void setup(ATMA::ATMAContext *l_ctx) override
    {
        ATMA_ENGINE_INFO("setting up benchmark game wrapper");
        active = true;
    }

    /**
     * real implementation of the game apps run function to house the
     * game loop
     */
    virtual void update(ATMA::ATMAContext *l_ctx, const double &l_dt) override
    {

        active = false;
        ATMA_ENGINE_INFO("completed benchmarks");
    }

    /**
     * real implementation of the game apps shut down function
     * to initiate shut down of the app
     */
    virtual void shutdown(ATMA::ATMAContext *l_ctx) override {}
};
