#ifndef ATMA_BENCH
#    define ATMA_BENCH
#    include "OAS/attributes/AttrRenderable.hpp"
#endif // !ATMA_BENCH
#include <atomina.hpp>
#include "Bench.hpp"
#include "OAS/Attribute.hpp"
#include "render/GLTexture.hpp"

/*
 * extension of the Game class from atomina-api
 * used as actual implementation
 */
class GameBenchmark: public ATMA::Game
{
public:
    std::shared_ptr<ATMA::AppWindow> m_win;

    // default constructor
    GameBenchmark() {}

    // deconstructor
    ~GameBenchmark() {}

    /**
     * real implementation of the game apps setup function to house the setup
     */
    virtual void setup(ATMA::ATMAContext *l_ctx) override
    {
        ATMA_ENGINE_INFO("setting up benchmark game wrapper");
        active = true;
        //======================================================CollideUpdateMultipleValues
        std::function<void(ATMA::ATMAContext *)> func = [](ATMA::ATMAContext *l_ctx)
        { l_ctx->m_sysMan->update(l_ctx, 0.0); };
        std::map<int, ATMA::ATMAContext *> values{};
        for(int i = 0; i < 20; i++)
        {
            ATMA::ATMAContext *ctx = this->initializeContext();
            for(int j = 0; j <= i; j++)
            {
                auto id = ctx->m_attrMan->createObject();
                ctx->m_attrMan->addAttribute(ctx, id, ATMA::AttributeType(ATMA::Attribute::Collidable));
            }
            values[i] = ctx;
        }
        ATMA_ENGINE_INFO("SysUpdate->update");
        Benchmark<ATMA::ATMAContext *> collideBenchmark{func, values};
        for(auto itr = values.begin(); itr != values.end(); itr++)
        {
            this->destoryContext(itr->second);
        }
        values.clear();
        //======================================================RenderLeakCheck
        func = [](ATMA::ATMAContext *l_ctx)
        {
            l_ctx->m_renderer->startScene(ATMA::Camera{
                {  0.f,   0.f},
                {320.f, 180.f}
            });
            l_ctx->m_sysMan->update(l_ctx, 0);
            l_ctx->m_renderer->finishScene(l_ctx);
        };
        ATMA::ATMAContext *ctx = this->initializeContext();
        auto winID = ctx->m_winMan->createWindow(ctx);
        m_win = ctx->m_winMan->getWindow(winID);
        m_win->setSize({1920, 1080});

        m_win->show();
        // note that the context is reset when set to a new window, so any memory associated with
        // it will cause an error. So best to set window before anything else
        ctx->m_renderer->setWindow(m_win);
        ctx->m_renderer->toggleBlend(true);
        ctx->m_renderer->toggleDepthTest(true);
        auto vertID = ctx->m_resMan->registerResource("vertex", 1u, "shader/defaultVertex.shader");
        auto fragID = ctx->m_resMan->registerResource("frag", 1u, "shader/defaultFrag.shader");
        auto vert = ctx->m_resMan->loadResource<ATMA::GLShader>(l_ctx, vertID);
        auto frag = ctx->m_resMan->loadResource<ATMA::GLShader>(l_ctx, fragID);
        vert->compile(ATMA::ShaderType::Vertex);
        frag->compile(ATMA::ShaderType::Fragment);
        auto prog = ATMA::GLProgram::makeProgram();
        prog->attachShader(vert);
        prog->attachShader(frag);
        prog->link();
        ctx->m_renderer->m_ctx->setShaderProgram(prog);
        auto backgroundID = ctx->m_resMan->registerResource("pixel", 0u, "res/Pixels.png");
        auto fontID = ctx->m_resMan->registerResource("font", 1u, "res/defaultFont.png");
        auto background = ctx->m_resMan->loadResource<ATMA::GLTexture>(l_ctx, backgroundID);
        auto font = ctx->m_resMan->loadResource<ATMA::GLTexture>(l_ctx, fontID);
        auto backObjID = ctx->m_attrMan->createObject();
        auto textObjID = ctx->m_attrMan->createObject();
        ATMA_ENGINE_TRACE("Adding renderables");
        ctx->m_attrMan->addAttribute(ctx, backObjID, ATMA::AttributeType(ATMA::Attribute::Renderable));
        auto renderable = ctx->m_attrMan->getAttribute<ATMA::AttrRenderable>(
            backObjID, ATMA::AttributeType(ATMA::Attribute::Renderable)
        );
        ATMA_ENGINE_TRACE("initialized renderable");
        renderable->m_self = std::make_shared<ATMA::Renderable>(ATMA::TransformContainer{
            ATMA::TransformElement{nullptr, ATMA::Transform{{0.f, 0.f}, {100.f, 100.f}}}
        });
        ATMA_ENGINE_TRACE("set texture transform");
        renderable->m_self->m_texture = background;
        ATMA_ENGINE_TRACE("added texture renderable");
        ctx->m_attrMan->addAttribute(ctx, textObjID, ATMA::AttributeType(ATMA::Attribute::Renderable));
        renderable = ctx->m_attrMan->getAttribute<ATMA::AttrRenderable>(
            textObjID, ATMA::AttributeType(ATMA::Attribute::Renderable)
        );
        renderable->m_self = std::make_shared<ATMA::Renderable>(ATMA::Text{
            ATMA::TextData{"Let's Bounce", {-85.f, 80.f}, {15.f, 15.f}, {16.f, 16.f}}
        });
        renderable->m_self->m_texture = font;
        ATMA_ENGINE_TRACE("added text renderable");
        for(int i = 0; i < 100; i++)
        {
            values[i] = ctx;
        }
        ATMA_ENGINE_INFO("SysUpdate->update");
        Benchmark<ATMA::ATMAContext *> renderBenchmark{func, values};
        this->destoryContext(ctx);
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
