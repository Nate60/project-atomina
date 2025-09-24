#pragma once
#include "pch.hpp"
#include "Camera.hpp"
#include "GUI/AppWindow.hpp"
#include "GLRenderContext.hpp"

namespace ATMA
{

    /**
     * used to handle drawing renderable objects to a target window
     */
    class Renderer
    {
    public:
        // default constructor
        Renderer();

        // deconstructor
        virtual ~Renderer();

        /**
         * enable texture blending
         * @param l_toggle set blending
         */
        void toggleBlend(const bool &l_toggle);

        /**
         * enable texture blending
         * @param l_toggle set blending
         */
        void toggleDepthTest(const bool &l_toggle);

        /**
         * define the size of the frame buffer
         * @param w width
         * @param h height
         */
        void setFrameBufferDimensions(const int &w, const int &h);

        /**
         * change the render target to a specific window
         * @param l_win shared pointer to target window
         */
        void setWindow(std::shared_ptr<AppWindow> l_win);

        /**
         * give the camera to render to draw a scene
         * @param l_camera to render from
         */
        void startScene(const Camera &l_camera);

        /**
         * add renderable to render queue
         * @param l_renderable to add
         */
        void addElement(const unsigned int &l_renderable);

        /**
         * remove element from render queue
         * @param l_renderable to remove
         */
        void removeElement(const unsigned int &l_renderable);

        /**
         * move elemnet to different render priority
         * @param l_renderable render object to move
         * @param l_z priority to render at
         */
        void changeElementPriority(const unsigned int &l_renderable, const short &l_z);

        /**
         * clear elements from render queue
         */
        void clearElements();

        /**
         * finish draw call
         */
        void finishScene(ATMAContext *l_ctx);

        std::shared_ptr<GLRenderContext> m_ctx;
    protected:
        std::map<short, std::vector<unsigned int>> m_elementContainer{};
    };

}
