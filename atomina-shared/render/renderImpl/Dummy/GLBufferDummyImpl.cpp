#include "pch.hpp"
#include "GLBufferDummyImpl.hpp"

namespace ATMA
{

    IndexBufferDummyImpl::IndexBufferDummyImpl(const std::vector<unsigned int> &l_data):
        IndexBuffer(l_data)
    {
        m_bindID = 0u;
    }

    IndexBufferDummyImpl::IndexBufferDummyImpl(): IndexBuffer()
    {
        m_bindID = 0u;
    }

    IndexBufferDummyImpl::~IndexBufferDummyImpl() {}

    void IndexBufferDummyImpl::setBuffer(const std::vector<unsigned int> &l_data)
    {
        m_data = l_data;
    }

    void IndexBufferDummyImpl::bind() {}

    void IndexBufferDummyImpl::unbind() {}

    VertexBufferDummyImpl::VertexBufferDummyImpl(const std::vector<float> &l_data):
        VertexBuffer(l_data)
    {
        m_bindID = 0u;
    }

    VertexBufferDummyImpl::VertexBufferDummyImpl(): VertexBuffer()
    {
        m_bindID = 0u;
    }

    VertexBufferDummyImpl::~VertexBufferDummyImpl() {}

    void VertexBufferDummyImpl::setBuffer(const std::vector<float> &l_data)
    {
        m_data = l_data;
    }

    void VertexBufferDummyImpl::bind() {}

    void VertexBufferDummyImpl::unbind() {}

    VertexArrayDummyImpl::VertexArrayDummyImpl(const std::vector<LayoutElement> &l_list):
        VertexArray(l_list)
    {
        m_bindID = 0u;
    }

    VertexArrayDummyImpl::VertexArrayDummyImpl(
        const std::initializer_list<LayoutElement> &l_elements
    ):
        VertexArray(l_elements)
    {
        m_bindID = 0u;
    }

    VertexArrayDummyImpl::VertexArrayDummyImpl(): VertexArray()
    {
        m_bindID = 0u;
    }

    VertexArrayDummyImpl::~VertexArrayDummyImpl() {}

    void VertexArrayDummyImpl::bind() {}

    void VertexArrayDummyImpl::bindLayout() {}

    void VertexArrayDummyImpl::setLayout(const std::vector<LayoutElement> &l_list)
    {
        m_elementSpecs = l_list;
    }

    void VertexArrayDummyImpl::unbind() {}

    void VertexArrayDummyImpl::unbindLayout() {}

}