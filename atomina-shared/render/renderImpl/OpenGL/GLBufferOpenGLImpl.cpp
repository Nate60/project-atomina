#include "pch.hpp"
#include "GLBufferOpenGLImpl.hpp"

namespace ATMA
{

    IndexBufferOpenGLImpl::IndexBufferOpenGLImpl(const std::vector<unsigned int> &l_data):
        IndexBuffer(l_data)
    {
        ATMA_ENGINE_TRACE("Creating OPEN GL Index Buffer");
        glGenBuffers(1, &m_bindID);
    }

    IndexBufferOpenGLImpl::IndexBufferOpenGLImpl(): IndexBuffer()
    {
        ATMA_ENGINE_TRACE("Creating OPEN GL Index Buffer");
        glGenBuffers(1, &m_bindID);
    }

    IndexBufferOpenGLImpl::~IndexBufferOpenGLImpl()
    {
        ATMA_ENGINE_TRACE("Deleting OPEN GL Index Buffer");
        glDeleteBuffers(1, &m_bindID);
    }

    void IndexBufferOpenGLImpl::setBuffer(const std::vector<unsigned int> &l_data)
    {
        ATMA_ENGINE_TRACE("setting OPEN GL Index Buffer");
        m_data = l_data;
    }

    void IndexBufferOpenGLImpl::bind()
    {
        ATMA_ENGINE_TRACE("binding OPEN GL Index Buffer");
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
        ATMA_ENGINE_TRACE("unbinding OPEN GL Index Buffer");
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    VertexBufferOpenGLImpl::VertexBufferOpenGLImpl(const std::vector<float> &l_data):
        VertexBuffer(l_data)
    {
        ATMA_ENGINE_TRACE("Creating OPEN GL Vertex Buffer");
        glGenBuffers(1, &m_bindID);
    }

    VertexBufferOpenGLImpl::VertexBufferOpenGLImpl(): VertexBuffer()
    {
        ATMA_ENGINE_TRACE("Creating OPEN GL Vertex Buffer");
        glGenBuffers(1, &m_bindID);
    }

    VertexBufferOpenGLImpl::~VertexBufferOpenGLImpl()
    {
        ATMA_ENGINE_TRACE("Deleting OPEN GL Vertex Buffer");
        glDeleteBuffers(1, &m_bindID);
    }

    void VertexBufferOpenGLImpl::setBuffer(const std::vector<float> &l_data)
    {
        ATMA_ENGINE_TRACE("setting OPEN GL Vertex Buffer");
        m_data = l_data;
    }

    void VertexBufferOpenGLImpl::bind()
    {
        ATMA_ENGINE_TRACE("binding OPEN GL Vertex Buffer");
        glBindBuffer(GL_ARRAY_BUFFER, m_bindID);
        glBufferData(GL_ARRAY_BUFFER, m_data.size() * sizeof(float), m_data.data(), GL_STATIC_DRAW);
    }

    void VertexBufferOpenGLImpl::unbind()
    {
        ATMA_ENGINE_TRACE("unbinding OPEN GL Vertex Buffer");
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    VertexArrayOpenGLImpl::VertexArrayOpenGLImpl(const std::vector<LayoutElement> &l_list):
        VertexArray(l_list)
    {
        ATMA_ENGINE_TRACE("Creating OPEN GL Vertex Array");
        glGenVertexArrays(1, &m_bindID);
    }

    VertexArrayOpenGLImpl::VertexArrayOpenGLImpl(
        const std::initializer_list<LayoutElement> &l_elements
    ):
        VertexArray(l_elements)
    {
        ATMA_ENGINE_TRACE("Creating OPEN GL Vertex Array");
        glGenVertexArrays(1, &m_bindID);
    }

    VertexArrayOpenGLImpl::VertexArrayOpenGLImpl(): VertexArray()
    {
        ATMA_ENGINE_TRACE("Creating OPEN GL Vertex Array");
        glGenVertexArrays(1, &m_bindID);
    }

    VertexArrayOpenGLImpl::~VertexArrayOpenGLImpl()
    {
        ATMA_ENGINE_TRACE("Deleting OPEN GL Vertex Array");
        glDeleteVertexArrays(1, &m_bindID);
    }

    void VertexArrayOpenGLImpl::bind()
    {
        ATMA_ENGINE_TRACE("binding OPEN GL Vertex Array");
        glBindVertexArray(m_bindID);
    }

    void VertexArrayOpenGLImpl::bindLayout()
    {
        ATMA_ENGINE_TRACE("binding OPEN GL Vertex Array Layout");
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
        ATMA_ENGINE_TRACE("setting OPEN GL Vertex Array Layout");
        m_elementSpecs = l_list;
    }

    void VertexArrayOpenGLImpl::unbind()
    {
        ATMA_ENGINE_TRACE("unbinding OPEN GL Vertex Array");
        glBindVertexArray(0);
    }

    void VertexArrayOpenGLImpl::unbindLayout()
    {
        ATMA_ENGINE_TRACE("unbinding OPEN GL Vertex Array Layout");
        for(int i = 0; i < m_elementSpecs.size(); i++)
        {
            glDisableVertexAttribArray(i);
        }
    }

}