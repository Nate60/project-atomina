#ifdef __linux__
#   pragma once
#   include "pch.hpp"
#   include "core/api.hpp"
#   include "GUI/AppWindow.hpp"

namespace ATMA{

    /**
     * Unix implementation of Application window using Xlib
    */
    class ATMA_API WindowUnixImpl: public AppWindow
    {
    public:
        //Constructor with all values defaulted so it can be a default constructor
        //specifies dimensons and window name
        WindowUnixImpl(
            const Vec2<int> &l_size = {180, 180},
            const std::string &l_name = "Atomina Application"
        );

        //default deconstructor 
        virtual ~WindowUnixImpl();

        
        /**
         * sets the size of the window to the new size
         * @param l_size new dimensions of the window
        */
        virtual void setSize(Vec2<int> l_size) override;

        /**
         * getter for window dimensions
         * @returns dimensions as a vector
        */
        virtual Vec2<int> getSize() override;


        /**
         * notify the window to show to the display
        */
        virtual void show() override;

        /**
         * get events that have been sent to the window and dispatch them
        */
        virtual void poll() override;
    protected:
        Display *m_display;
        Window m_window;
        int m_screen;
        friend class GLRenderContextOpenGLUnixImpl;
    };

}
#else
#    error Linux implementation included in non-linux target
#endif