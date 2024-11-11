#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "render/GLRenderContext.hpp"

namespace ATMA
{

    /**
     * @brief Dummy implementation of a shader program
     */
    class GLRenderContextDummyImpl: public GLRenderContext
    {
    public:
        // default constructor
        GLRenderContextDummyImpl();

        // default deconstructor
        virtual ~GLRenderContextDummyImpl();

        virtual void init() override;

        /**
         * Sets the size of the current view port that he render context is drawing to
         * @param l_size dimensions of the new viewport
         */
        virtual void setViewPort(const Vec2<int> &l_pos, const Vec2<int> &l_size) override;


        /**
         * clears the view port that he Render context has been set to
         * to be all one colour
         */
        virtual void clear() override;

        virtual void toggleBlend(const bool &l_toggle) override;
    };

}