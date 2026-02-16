#pragma once
#include "pch.hpp"
#include "Transform.hpp"
#include "GLTexture.hpp"
#include "resource/graphics/Animation.hpp"

namespace ATMA
{

    typedef std::pair<std::shared_ptr<Animation>, Transform> TransformElement;
    typedef std::vector<TransformElement> TransformContainer;

    class Renderable: public TransformContainer
    {
    public:
        Renderable();
        Renderable(const Renderable &l_other);
        Renderable(Renderable &&l_other);
        Renderable(TransformContainer &&l_other);

        void operator=(const Renderable &l_other);
        void operator=(Renderable &&l_other);

        std::shared_ptr<GLTexture> m_texture;
    };
}
