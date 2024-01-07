#include "pch.hpp"
#include "GLBufferOpenGLImpl.hpp"

namespace ATMA
{

    IndexBufferOpenGLImpl::IndexBufferOpenGLImpl(const std::vector<unsigned int> &l_data):
        IndexBuffer(l_data)
    {
        glGenBuffers(1, &m_bindID);
    }

    IndexBufferOpenGLImpl::IndexBufferOpenGLImpl(): IndexBuffer()
    {
        glGenBuffers(1, &m_bindID);
    }

    IndexBufferOpenGLImpl::~IndexBufferOpenGLImpl()
    {
        glDeleteBuffers(1, &m_bindID);
    }

    void IndexBufferOpenGLImpl::setBuffer(const std::vector<unsigned int> &l_data)
    {
        m_data = l_data;
    }

    void IndexBufferOpenGLImpl::bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bindID);
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            m_data.size() * sizeof(unsigned int),
            m_data.data(),
            GL_STATIC_DRAW
        );
    }

    void IndexBufferOpenGLImpl::unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    VertexBufferOpenGLImpl::VertexBufferOpenGLImpl(const std::vector<float> &l_data):
        VertexBuffer(l_data)
    {
        glGenBuffers(1, &m_bindID);
    }

    VertexBufferOpenGLImpl::VertexBufferOpenGLImpl(): VertexBuffer()
    {
        glGenBuffers(1, &m_bindID);
    }

    VertexBufferOpenGLImpl::~VertexBufferOpenGLImpl()
    {
        glDeleteBuffers(1, &m_bindID);
    }

    void VertexBufferOpenGLImpl::setBuffer(const std::vector<float> &l_data)
    {
        m_data = l_data;
    }

    void VertexBufferOpenGLImpl::bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_bindID);
        glBufferData(GL_ARRAY_BUFFER, m_data.size() * sizeof(float), m_data.data(), GL_STATIC_DRAW);
    }

    void VertexBufferOpenGLImpl::unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    VertexArrayOpenGLImpl::VertexArrayOpenGLImpl(const std::vector<LayoutElement> &l_list):
        VertexArray(l_list)
    {
        glGenVertexArrays(1, &m_bindID);
    }

    VertexArrayOpenGLImpl::VertexArrayOpenGLImpl(
        const std::initializer_list<LayoutElement> &l_elements
    ):
        VertexArray(l_elements)
    {
        glGenVertexArrays(1, &m_bindID);
    }

    VertexArrayOpenGLImpl::VertexArrayOpenGLImpl(): VertexArray()
    {
        glGenVertexArrays(1, &m_bindID);
    }

    VertexArrayOpenGLImpl::~VertexArrayOpenGLImpl()
    {
        glDeleteVertexArrays(1, &m_bindID);
    }

    void VertexArrayOpenGLImpl::bind()
    {
        glBindVertexArray(m_bindID);
    }

    void VertexArrayOpenGLImpl::bindLayout()
    {
        for(int i = 0; i < m_elementSpecs.size(); i++)
        {

            glVertexAttribPointer(
                i,
                m_elementSpecs[i].m_vertCount,
                GL_FLOAT,
                GL_FALSE,
                m_elementSpecs[i].m_stride * sizeof(float),
                (void *)(m_elementSpecs[i].m_offset * sizeof(float))
            );
            glEnableVertexAttribArray(i);
        }
    }

    void VertexArrayOpenGLImpl::setLayout(const std::vector<LayoutElement> &l_list)
    {
        m_elementSpecs = l_list;
    }

    void VertexArrayOpenGLImpl::unbind()
    {
        glBindVertexArray(0);
    }

    void VertexArrayOpenGLImpl::unbindLayout()
    {
        for(int i = 0; i < m_elementSpecs.size(); i++)
        {
            glDisableVertexAttribArray(i);
        }
    }

}