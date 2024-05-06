#include "pch.hpp"
#include "GLBuffer.hpp"
#ifdef ATMA_OPENGL
#    include "renderImpl/OpenGL/GLBufferOpenGLImpl.hpp"
#    define __ATMAMAKEGLBUFFER(bufferType, bufferData)                                             \
        return std::make_shared<bufferType##OpenGLImpl>(bufferData)
#    define __ATMAMAKEEMPTYGLBUFFER(bufferType) return std::make_shared<bufferType##OpenGLImpl>()
#else
#    include "renderImpl/Dummy/GLBufferDummyImpl.hpp"
#    define __ATMAMAKEGLBUFFER(bufferType, bufferData)                                             \
        return std::make_shared<bufferType##DummyImpl>(bufferData)
#    define __ATMAMAKEEMPTYGLBUFFER(bufferType) return std::make_shared<bufferType##DummyImpl>()
#endif

namespace ATMA
{

    IndexBuffer::IndexBuffer(const std::vector<unsigned int> &l_data)
    {
        ATMA_ENGINE_TRACE("Creating Index Buffer");
        m_data = l_data;
    }

    IndexBuffer::IndexBuffer() 
    {
        ATMA_ENGINE_TRACE("Creating Index Buffer");
        m_data = {};
    }

    IndexBuffer::~IndexBuffer() 
    {
        ATMA_ENGINE_TRACE("Deleting Index Buffer");
    }

    std::shared_ptr<IndexBuffer> IndexBuffer::makeBuffer(const std::vector<unsigned int> &l_data)
    {
        __ATMAMAKEGLBUFFER(IndexBuffer, l_data);
    }

    std::shared_ptr<IndexBuffer> IndexBuffer::makeBuffer()
    {
        __ATMAMAKEEMPTYGLBUFFER(IndexBuffer);
    }

    VertexBuffer::VertexBuffer(const std::vector<float> &l_data): m_data(l_data) 
    {
        ATMA_ENGINE_TRACE("Creating Vertex Buffer");
    }

    VertexBuffer::VertexBuffer()
    {
        ATMA_ENGINE_TRACE("Creating Vertex Buffer");
        m_data = {};
    }

    std::shared_ptr<VertexBuffer> VertexBuffer::makeBuffer(const std::vector<float> &l_data)
    {
        __ATMAMAKEGLBUFFER(VertexBuffer, l_data);
    }

    std::shared_ptr<VertexBuffer> VertexBuffer::makeBuffer()
    {
        __ATMAMAKEEMPTYGLBUFFER(VertexBuffer);
    }

    VertexBuffer::~VertexBuffer() 
    {
        ATMA_ENGINE_TRACE("Deleting Vertex Buffer");
    }

    VertexArray::VertexArray(const std::vector<LayoutElement> &l_elements):
        m_elementSpecs(l_elements)
    {
        ATMA_ENGINE_TRACE("Creating Vertex Array");
    }

    VertexArray::VertexArray(const std::initializer_list<LayoutElement> &l_elements)
    {
        ATMA_ENGINE_TRACE("Creating Vertex Array");
        for(auto &l_element: l_elements)
            m_elementSpecs.emplace_back(l_element);
    }

    VertexArray::VertexArray()
    {
        ATMA_ENGINE_TRACE("Creating Vertex Array");
        m_elementSpecs = {};
    }

    std::shared_ptr<VertexArray> VertexArray::makeBuffer(const std::vector<LayoutElement> &l_list)
    {
        __ATMAMAKEGLBUFFER(VertexArray, l_list);
    }

    std::shared_ptr<VertexArray>
    VertexArray::makeBuffer(const std::initializer_list<LayoutElement> &l_list)
    {
        __ATMAMAKEGLBUFFER(VertexArray, l_list);
    }

    std::shared_ptr<VertexArray> VertexArray::makeBuffer()
    {
        __ATMAMAKEEMPTYGLBUFFER(VertexArray);
    }

    VertexArray::~VertexArray() 
    {
        ATMA_ENGINE_TRACE("Deleting Vertex Array");
    }
}