#include "pch.hpp"
#include "BufferGLADImpl.hpp"

namespace ATMA
{

    IndexBufferGLADImpl::IndexBufferGLADImpl(const std::vector<unsigned int> &l_data):
        IndexBuffer(l_data)
    {
        glGenBuffers(1, &m_bindID);
    }

    IndexBufferGLADImpl::IndexBufferGLADImpl(): IndexBuffer()
    {
        glGenBuffers(1, &m_bindID);
    }

    IndexBufferGLADImpl::~IndexBufferGLADImpl()
    {
        glDeleteBuffers(1, &m_bindID);
    }

    void IndexBufferGLADImpl::setBuffer(const std::vector<unsigned int> &l_data)
    {
        m_data = l_data;
    }

    void IndexBufferGLADImpl::bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bindID);
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            m_data.size() * sizeof(unsigned int),
            m_data.data(),
            GL_STATIC_DRAW
        );
    }

    void IndexBufferGLADImpl::unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    VertexBufferGLADImpl::VertexBufferGLADImpl(const std::vector<float> &l_data):
        VertexBuffer(l_data)
    {
        glGenBuffers(1, &m_bindID);
    }

    VertexBufferGLADImpl::VertexBufferGLADImpl(): VertexBuffer()
    {
        glGenBuffers(1, &m_bindID);
    }

    VertexBufferGLADImpl::~VertexBufferGLADImpl()
    {
        glDeleteBuffers(1, &m_bindID);
    }

    void VertexBufferGLADImpl::setBuffer(const std::vector<float> &l_data)
    {
        m_data = l_data;
    }

    void VertexBufferGLADImpl::bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_bindID);
        glBufferData(GL_ARRAY_BUFFER, m_data.size() * sizeof(float), m_data.data(), GL_STATIC_DRAW);
    }

    void VertexBufferGLADImpl::unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    VertexArrayGLADImpl::VertexArrayGLADImpl(const std::vector<LayoutElement> &l_list):
        VertexArray(l_list)
    {
        glGenVertexArrays(1, &m_bindID);
    }

    VertexArrayGLADImpl::VertexArrayGLADImpl(const std::initializer_list<LayoutElement> &l_elements
    ):
        VertexArray(l_elements)
    {
        glGenVertexArrays(1, &m_bindID);
    }

    VertexArrayGLADImpl::VertexArrayGLADImpl(): VertexArray()
    {
        glGenVertexArrays(1, &m_bindID);
    }

    VertexArrayGLADImpl::~VertexArrayGLADImpl()
    {

        glDeleteVertexArrays(1, &m_bindID);
    }

    void VertexArrayGLADImpl::bind()
    {
        glBindVertexArray(m_bindID);
    }

    void VertexArrayGLADImpl::bindLayout()
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

    void VertexArrayGLADImpl::setLayout(const std::vector<LayoutElement> &l_list)
    {
        m_elementSpecs = l_list;
    }

    void VertexArrayGLADImpl::unbind()
    {
        glBindVertexArray(0);
    }

    void VertexArrayGLADImpl::unbindLayout()
    {
        for(int i = 0; i < m_elementSpecs.size(); i++)
        {
            glDisableVertexAttribArray(i);
        }
    }

}