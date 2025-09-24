#include "OAS/attributes/AttrRenderable.hpp"
#include "render/Renderable.hpp"
#include <atomina.hpp>
#include "render/Tilemap.hpp"
#include "resource/writers/TilesetWriter.hpp"
#include "util/Log.hpp"
#include <memory>

class RunState: public ATMA::BaseState
{
public:
    // default constructor
    RunState(ATMA::ATMAContext *l_ctx): BaseState(l_ctx)
    {
        m_obj = l_ctx->m_attrMan->createObject();
        m_backgroundObj = l_ctx->m_attrMan->createObject();
        m_textObj = l_ctx->m_attrMan->createObject();
        m_mapObj = l_ctx->m_attrMan->createObject();
        m_animID = l_ctx->m_resMan->registerResource("anim", 2u, "res/Ball.anim");
        m_textureID = l_ctx->m_resMan->registerResource("texture", 0u, "res/Ball.png");
        m_backgroundID = l_ctx->m_resMan->registerResource("pixel", 0u, "res/Pixels.png");
        m_fontID = l_ctx->m_resMan->registerResource("font", 1u, "res/defaultFont.png");
        m_mapdataID = l_ctx->m_resMan->registerResource("mapdata", 3u, "res/test.map");
        m_tileSetID = l_ctx->m_resMan->registerResource("tileset", 4u, "res/test.mts");
        m_tilesID = l_ctx->m_resMan->registerResource("tiles", 0u, "res/tiles.png");
        m_anim = l_ctx->m_resMan->loadResource<ATMA::Animation>(l_ctx, m_animID);
        m_texture = l_ctx->m_resMan->loadResource<ATMA::GLTexture>(l_ctx, m_textureID);
        m_background = l_ctx->m_resMan->loadResource<ATMA::GLTexture>(l_ctx, m_backgroundID);
        m_font = l_ctx->m_resMan->loadResource<ATMA::GLTexture>(l_ctx, m_fontID);
        m_mapdata = l_ctx->m_resMan->loadResource<ATMA::Mapdata>(l_ctx, m_mapdataID);
        m_tileset = l_ctx->m_resMan->loadResource<ATMA::Tileset>(l_ctx, m_tileSetID);
        m_tiles = l_ctx->m_resMan->loadResource<ATMA::GLTexture>(l_ctx, m_tilesID);
        ATMA_ENGINE_INFO("finished loading resources");
    }

    /**
     * function called by context when activating state
     */
    void activate(ATMA::ATMAContext *l_ctx) override
    {
        std::shared_ptr<ATMA::Animation> anim = std::make_shared<ATMA::Animation>(ATMA::AnimationData{
            "pixels",
            6,
            3,
            {1.f, 1.f},
            {0.f, 2.f},
            std::vector<ATMA::FrameData>{
              {4, std::bitset<ATConst::BITSET_SIZE>{}},
              {4, std::bitset<ATConst::BITSET_SIZE>{}},
              {4, std::bitset<ATConst::BITSET_SIZE>{}},
              {4, std::bitset<ATConst::BITSET_SIZE>{}},
              {4, std::bitset<ATConst::BITSET_SIZE>{}},
              {4, std::bitset<ATConst::BITSET_SIZE>{}}
            },
            true
        });
        ATMA_ENGINE_TRACE("Setting up objects");
        l_ctx->m_attrMan->addAttribute(l_ctx, m_obj, ATMA::AttributeType(ATMA::Attribute::Renderable));
        l_ctx->m_attrMan->addAttribute(l_ctx, m_backgroundObj, ATMA::AttributeType(ATMA::Attribute::Renderable));
        l_ctx->m_attrMan->addAttribute(l_ctx, m_textObj, ATMA::AttributeType(ATMA::Attribute::Renderable));
        l_ctx->m_attrMan->addAttribute(l_ctx, m_mapObj, ATMA::AttributeType(ATMA::Attribute::Renderable));

        ATMA_ENGINE_TRACE("Setting object values");

        auto renderAttr = l_ctx->m_attrMan->getAttribute<ATMA::AttrRenderable>(
            m_obj, ATMA::AttributeType(ATMA::Attribute::Renderable)
        );
        ATMA::Transform tt{};
        tt.m_size = ATMA::Vec2<float>{100.f, 100.f};
        tt.m_selectPos = ATMA::Vec2<float>{0.f, 64.f};
        tt.m_selectSize = ATMA::Vec2<float>{64.f, 64.f};
        renderAttr->m_self = std::make_shared<ATMA::Renderable>(ATMA::TransformContainer{
            ATMA::TransformElement{m_anim, tt}
        });
        renderAttr->m_self->m_texture = m_texture;
        l_ctx->m_renderer->changeElementPriority(m_backgroundObj, -1);
        ATMA_ENGINE_TRACE("Setting background values");
        renderAttr = l_ctx->m_attrMan->getAttribute<ATMA::AttrRenderable>(
            m_backgroundObj, ATMA::AttributeType(ATMA::Attribute::Renderable)
        );
        tt = ATMA::Transform{};
        tt.m_size = ATMA::Vec2<float>{100.f, 100.f};
        renderAttr->m_self = std::make_shared<ATMA::Renderable>(ATMA::TransformContainer{
            ATMA::TransformElement{m_anim, tt}
        });
        renderAttr->m_self->m_texture = m_background;
        ATMA_ENGINE_TRACE("Setting text values");
        ATMA_ENGINE_TRACE("Setting text text");
        renderAttr = l_ctx->m_attrMan->getAttribute<ATMA::AttrRenderable>(
            m_textObj, ATMA::AttributeType(ATMA::Attribute::Renderable)
        );
        renderAttr->m_self = std::make_shared<ATMA::Renderable>(ATMA::Text{
            {"Let's Bounce", {-85.f, 80.f}, {15.f, 15.f}, {16.f, 16.f}}
        });
        renderAttr->m_self->m_texture = m_font;

        renderAttr = l_ctx->m_attrMan->getAttribute<ATMA::AttrRenderable>(
            m_mapObj, ATMA::AttributeType(ATMA::Attribute::Renderable)
        );
        renderAttr->m_self = std::make_shared<ATMA::Renderable>(ATMA::Tilemap{
            {m_tileset, m_mapdata, {0.f, 0.f}, 96}
        });
        renderAttr->m_self->m_texture = m_tiles;
        l_ctx->m_renderer->changeElementPriority(m_mapObj, 3);
        ATMA_ENGINE_TRACE("Run state activation complete");
    }

    /**
     * function called by context when deactivating state
     */
    void deactivate(ATMA::ATMAContext *l_ctx) override
    {
        l_ctx->m_attrMan->clearObject(l_ctx, m_obj);
        l_ctx->m_attrMan->clearObject(l_ctx, m_backgroundObj);
        l_ctx->m_attrMan->clearObject(l_ctx, m_textObj);
    }

    /**
     * gives the type id of the state
     * each state should give a different type id
     * @returns type id of the state
     */
    unsigned int getId() const override
    {
        return ATMA::StateType(ATMA::State::COUNT);
    }

    /**
     * passes window events to be handled by the state
     * @param l_ctx Engine Context
     * @param l_winEvent the event generated by the window
     * @returns whether or not the event was handled
     */
    void handleInput(ATMA::ATMAContext *l_ctx, const ATMA::WindowEvent &l_winEvent) override {}

    unsigned int m_obj;
    unsigned int m_backgroundObj;
    unsigned int m_textObj;
    unsigned int m_animID;
    unsigned int m_mapObj;
    std::shared_ptr<ATMA::Animation> m_anim;
    unsigned int m_textureID;
    std::shared_ptr<ATMA::GLTexture> m_texture;
    unsigned int m_backgroundID;
    std::shared_ptr<ATMA::GLTexture> m_background;
    unsigned int m_tilesID;
    std::shared_ptr<ATMA::GLTexture> m_tiles;
    unsigned int m_vertID;
    std::shared_ptr<ATMA::GLShader> m_vert;
    unsigned int m_fragID;
    std::shared_ptr<ATMA::GLShader> m_frag;
    unsigned int m_fontID;
    std::shared_ptr<ATMA::GLTexture> m_font;
    std::shared_ptr<ATMA::GLProgram> m_prog;
    unsigned int m_mapdataID;
    std::shared_ptr<ATMA::Mapdata> m_mapdata;
    unsigned int m_tileSetID;
    std::shared_ptr<ATMA::Tileset> m_tileset;
};
