#pragma once
#include "pch.hpp"
#include "core/api.hpp"

namespace ATMA
{

    using ViewId = unsigned int;

    /**
     * Atomina implementation of a window as well as the container for 
     * for any inputs from the user. Currently just a wrapper for SFML
     * RenderWindow
     */
    class ATMA_API Window
    {
    public:

        //constructor specifying name and dimensions of the window
        Window(
            const std::string &l_name = "Project Atomina",
            const sf::Vector2u &l_dimensions = {640, 480}
        );

        //copy constructor
        Window(const Window &l_other);

        //deconstructor
        ~Window();

        /**
         * begin drawing to the next frame to be displayed 
         */
        void beginDraw();

        /**
         * stop the drawing to the next frame and allow it to be displayed 
         */
        void endDraw();

        /**
         * check if window is finished operation
         * @returns if the window is finished
         */
        bool isDone() const;

        /**
         * check if the window has been fullscreened
         * @returns if the window has been fullscreened 
         */
        bool isFullscreen() const;

        /**
         * check if the window is in focus
         * @returns if the window is the current focus 
         */
        bool isFocused() const;

        /**
         * switches to and from fullscreen 
         */
        void toggleFullscreen();

        /**
         * Closes the window 
         */
        void close();

        /**
         * gets the dimensions of the current window
         * @returns the dimensions of the current window as an unsigned int vector
         */
        sf::Vector2u getWindowSize();

        /**
         * gets the region of the view for the window
         * @returns rectangle specifying region of the view 
         */
        sf::Rect<float> getViewSpace();

        /**
         * polls the window for events
         * @param l_e reference event to push oldest event to
         * @returns if an event was pushed 
         */
        bool poll(sf::Event &l_e);

        /**
         * clears the frame displayed on the window 
         */
        void clear();

        /**
         * pushes the next frame to the window display 
         */
        void display();

        /**
         * draws drawable object to the windows self contained
         * render target
         * @param l_drawable object to draw to the window
         * @param l_states render states of the render target
         */
        void draw(
            const sf::Drawable &l_drawable,
            const sf::RenderStates &l_states = sf::RenderStates::Default
        );

        //stream reader for getting window name
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