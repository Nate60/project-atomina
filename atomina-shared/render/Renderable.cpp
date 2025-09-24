#include "Renderable.hpp"

namespace ATMA
{
    Renderable::Renderable(): TransformContainer(), m_texture(nullptr) {}

    Renderable::Renderable(const Renderable &l_other): TransformContainer(l_other), m_texture(l_other.m_texture) {}

    Renderable::Renderable(Renderable &&l_other): TransformContainer(l_other), m_texture(l_other.m_texture) {}

    Renderable::Renderable(TransformContainer &&l_other): TransformContainer(l_other), m_texture(nullptr) {}

    void Renderable::operator=(const Renderable &l_other)
    {
        this->m_texture = l_other.m_texture;
        this->clear();
        this->reserve(l_other.size());
        this->assign(l_other.begin(), l_other.end());
    }

    void Renderable::operator=(Renderable &&l_other)
    {
        this->m_texture = l_other.m_texture;
        this->clear();
        this->reserve(l_other.size());
        this->assign(l_other.begin(), l_other.end());
    }
}
