#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "render/GLRenderable.hpp"
#include "render/GLRenderContext.hpp"

namespace ATMA
{

    class ATMA_API GLRenderer
    {
    public:
        // default deconstructor
        virtual ~GLRenderer();

        void draw(std::shared_ptr<GLRenderable> r);

        void setWindow(std::shared_ptr<AppWindow> l_window);
    protected:
        std::unique_ptr<GLRenderContext> m_Ctx{};
    private:
        // Do not want the constructor to be called outside of Engine Context
        //  default constructor
        GLRenderer();
        friend class ATMAContext;
    };

}