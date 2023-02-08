#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "util/Props.hpp"
#include "math/Vec2.hpp"
#include "render/RenderContext.hpp"

namespace ATMA
{

    class RenderContext;

    /**
     * @brief Abstracted window provides api for manipulating windows
     * regardless of library implementation
     */
    class ATMA_API Window
    {
    public:
        // constructor specifying window name
        Window(const std::string &l_name = "ATMA_APP");

        // constructor specifying window properties and name
        Window(const Props &l_props, const std::string &l_name = "ATMA_APP");

        // default deconstructor
        virtual ~Window();

        /**
         * @brief sets input function to be called when window encounters an input
         * @param l_callback function to be called
         */
        virtual void setInputCallback(std::function<void(Window *, int, int, int, int)> l_callback
        ) = 0;

        /**
         * @brief sets function to be called when the window encounters a resize event
         * @param l_callback function to be called
         */
        virtual void setFrameResizeCallback(std::function<void(Window *, int, int)> l_callback) = 0;

        /**
         * @brief swaps the updated buffer to be displayed
         */
        virtual void swapBuffers() = 0;

        /**
         * @brief polls the window for any events
         */
        virtual void pollEvents() = 0;

        /**
         * @brief switched the render context to link to this window
         * @param l_context render context from main context
         */
        virtual void focusContext(const std::unique_ptr<RenderContext> &l_context) = 0;

        /**
         * @brief toggle flag to determine if window should close
         * @param l_bool toggles flag
         */
        virtual void setWindowShouldClose(bool l_bool) = 0;

        /**
         * @brief checks flag if window should close
         * @return value of flag
         */
        virtual bool getWindowShouldClose() const = 0;

        /**
         * @brief gets dimensions of the windows frame
         * @return dimensions as a vector
         */
        virtual Vec2<int> getFrameBufferSize() const = 0;

        const std::string m_name;
    protected:
        Props m_props;
        std::unique_ptr<RenderContext> m_renderContext;
    };

}