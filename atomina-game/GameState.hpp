#pragma once
#include <atomina.hpp>

using namespace std::placeholders;

/**
 * Game Implementation of state to implement a user defined extended state
 * that is external to the engine
 */
class GameState: public ATMA::BaseState
{
public:
    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();

    // default constructor
    GameState(): BaseState() {}

    /**
     * Game app implementation of onCreate function to be the initialization
     * of the game app user defined objects
     */
    virtual void onCreate() override {}

    /**
     * stub implementation of onDestroy
     */
    virtual void onDestroy() override {}

    /**
     * stub implementation of activate function
     */
    virtual void activate() override
    {
        auto win = ctx.getWindow(ATConst::MAIN_WINDOW_ID);
        for(auto &option: m_menuOpts)
        {
            option = ctx.createObject();
            ctx.addAttribute(option, ATMA::AttributeType(ATMA::Attribute::Shape));
            ctx.addAttribute(option, ATMA::AttributeType(ATMA::Attribute::Sprite));
            ctx.addAttribute(option, ATMA::AttributeType(ATMA::Attribute::Renderable));
            auto render = ctx.getAttribute<ATMA::AttrRenderable>(
                option, ATMA::AttrType(ATMA::Attribute::Renderable)
            );
            render->m_program = ATMA::ShaderProgram::makeDefaultProgram();
        }

        auto selectedtextid = ctx.registerResource("selected", 1, "res\\selected.png");
        auto unselectedtextid = ctx.registerResource("unselected", 1, "res\\unselected.png");
        auto fontid = ctx.registerResource("font", 2, "res\\defaultFont.png");
        m_selectedTexture = ctx.loadResource<ATMA::Texture>(selectedtextid);
        m_unselectedTexture = ctx.loadResource<ATMA::Texture>(unselectedtextid);

        auto sprite1 = ctx.getAttribute<ATMA::AttrSprite>(
            m_menuOpts[0], ATMA::AttrType(ATMA::Attribute::Sprite)
        );
        auto sprite2 = ctx.getAttribute<ATMA::AttrSprite>(
            m_menuOpts[1], ATMA::AttrType(ATMA::Attribute::Sprite)
        );

        sprite1->m_texture = m_selectedTexture;
        sprite2->m_texture = m_unselectedTexture;

        auto pos1 = ctx.getAttribute<ATMA::AttrShape>(
            m_menuOpts[0], ATMA::AttrType(ATMA::Attribute::Shape)
        );
        auto pos2 = ctx.getAttribute<ATMA::AttrShape>(
            m_menuOpts[1], ATMA::AttrType(ATMA::Attribute::Shape)
        );

        auto renderer = ctx.getRenderer();
        renderer->setFont(ctx.loadResource<ATMA::Font>(fontid));
        renderer->drawText("Start Game", {-0.2f, 0.1f}, {0.05f, 0.05f}, 0);

        pos1->m_pos = {0.f, -0.2f};
        pos2->m_pos = {0.f, 0.2f};
        pos1->m_size = {0.25f, 0.1f};
        pos2->m_size = {0.25f, 0.1f};

        win->setInputCallback(std::bind(&GameState::inputCallback, this, _1, _2, _3, _4, _5));
    }

    /**
     * stub implementation of deactive function
     */
    virtual void deactivate() override {}

    /**
     * gets state id
     * @returns state id
     */
    virtual unsigned int getId() const override
    {
        return ATMA::StateType(ATMA::State::COUNT);
    }

    void inputCallback(ATMA::Window *window, int key, int scancode, int action, int mods)
    {
        if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            window->setWindowShouldClose(true);
        if((key == GLFW_KEY_DOWN || key == GLFW_KEY_UP) && action == GLFW_PRESS)
        {
            auto sprite1 = ctx.getAttribute<ATMA::AttrSprite>(
                m_menuOpts[0], ATMA::AttrType(ATMA::Attribute::Sprite)
            );
            auto sprite2 = ctx.getAttribute<ATMA::AttrSprite>(
                m_menuOpts[1], ATMA::AttrType(ATMA::Attribute::Sprite)
            );

            std::swap(sprite1->m_texture, sprite2->m_texture);
        }
    }
private:
    unsigned int m_menuOpts[2] = {0, 0};
    int m_selected = 0;
    std::shared_ptr<ATMA::Texture> m_selectedTexture = 0;
    std::shared_ptr<ATMA::Texture> m_unselectedTexture = 0;
};
