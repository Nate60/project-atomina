#pragma once
#include "pch.hpp"
#include "core/api.hpp"

namespace ATMA
{

    using ViewId = unsigned int;

    class ATMA_API Window
    {
    public:
        Window(
            const std::string &l_name = "Project Atomina",
            const sf::Vector2u &l_dimensions = {640, 480}
        );

        Window(const Window &l_other);

        ~Window();

        void beginDraw();
        void endDraw();

        void update();

        bool isDone() const;
        bool isFullscreen() const;
        bool isFocused() const;

        void toggleFullscreen();
        void close();

        sf::Vector2u getWindowSize();
        sf::Rect<float> getViewSpace();

        bool poll(sf::Event &l_e);

        void clear();
        void display();
        void draw(
            const sf::Drawable &l_drawable,
            const sf::RenderStates &l_states = sf::RenderStates::Default
        );
        ATMA_API friend std::ostream& operator<<(std::ostream& os, const  std::shared_ptr<Window> w);
    private:
        std::unordered_map<ViewId, sf::View> m_layers;
        bool m_done{false};
        bool m_fullscreen{false};
        bool m_focused{false};
        std::string m_name{""};
        sf::RenderWindow m_window;
    };

}