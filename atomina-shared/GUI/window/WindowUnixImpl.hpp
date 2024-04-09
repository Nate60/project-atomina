#ifdef __linux__
#    pragma once
#    include "pch.hpp"
#    include "core/api.hpp"
#    include "GUI/AppWindow.hpp"

namespace ATMA
{

    /**
     * Unix implementation of Application window using Xlib
     */
    class ATMA_API WindowUnixImpl: public AppWindow
    {
    public:
        // Constructor with all values defaulted so it can be a default constructor
        // specifies dimensons and window name
        WindowUnixImpl(
            const Vec2<unsigned int> &l_size = {320, 320},
            const std::string &l_name = "Atomina Application"
        );

        // default deconstructor
        virtual ~WindowUnixImpl();

        /**
         * sets the size of the window to the new size
         * @param l_size new dimensions of the window
         */
        virtual void setSize(const Vec2<unsigned int> &l_size) override;

        /**
         * notify the window to show to the display
         */
        virtual void show() override;

        /**
         * get events that have been sent to the window and dispatch them
         */
        virtual void poll() override;

        /**
         * Swap the graphic buffers and bring the drawn buffer to the front
         */
        virtual void swapBuffers() override;

        /**
         * Getter for the under lying parent display of the window
         * @returns parent Xlib Display pointer
         */
        static Display *getDisplay();

        /**
         * static Getter for the Frame buffer config of the given display
         * @param display the display for which to get the frame buffer config for
         * @returns Graphics XLib Frame buffer config for the given display
         */
        static GLXFBConfig getFrameBufferConfig(Display *display);
    protected:
        static const long constexpr EVENT_MASK =
            ExposureMask | KeyPressMask | KeyReleaseMask | StructureNotifyMask | FocusChangeMask;
        Display *m_display;
        Window m_root;
        Window m_window;
        Colormap m_colourMap;
        int m_screen;
        Atom m_deleteMessage;
        bool m_repeatKey = false;
        friend class GLRenderContextOpenGLUnixImpl;

        void redraw();
    };

}
#else
#    error Linux implementation included in non-linux target
#endif