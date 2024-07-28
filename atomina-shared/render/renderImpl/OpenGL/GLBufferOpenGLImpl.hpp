#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "render/GLBuffer.hpp"

namespace ATMA
{
    /**
     * @brief OpenGL implementation of Index Buffer
     */
    class IndexBufferOpenGLImpl: public IndexBuffer
    {
    public:
        // constructor specifying the data in the buffer
        IndexBufferOpenGLImpl(const std::vector<unsigned int> &l_data);

        // default constructor
        IndexBufferOpenGLImpl();

        // default deconstructor
        virtual ~IndexBufferOpenGLImpl();

        /**
         * @brief update the internal data of the buffer
         * @param l_data new data
         */
        virtual void setBuffer(const std::vector<unsigned int> &l_data) override;

        /**
         * @brief binds buffer to GL context
         */
        virtual void bind() override;

        /**
         * @brief unbinds buffer from GL context
         */
        virtual void unbind() override;
    };

    /**
     * @brief OpenGL implementation of Vertex Buffer
     */
    class VertexBufferOpenGLImpl: public VertexBuffer
    {
    public:
        // constructor specifying the data in the buffer
        VertexBufferOpenGLImpl(const std::vector<float> &l_data);

        // default constructor
        VertexBufferOpenGLImpl();

        // default deconstructor
        virtual ~VertexBufferOpenGLImpl();

        /**
         * @brief update the internal data of the buffer
         * @param l_data new data
         */
        virtual void setBuffer(const std::vector<float> &l_data) override;

        /**
         * @brief binds buffer to GL context
         */
        virtual void bind() override;

        /**
         * @brief unbinds buffer from GL context
         */
        virtual void unbind() override;
    };

    /**
     * @brief OpenGL implementation of Vertex Array
     */
    class VertexArrayOpenGLImpl: public VertexArray
    {
    public:
        // constructor specifying layout as a vector
        VertexArrayOpenGLImpl(const std::vector<LayoutElement> &l_list);

        // constructor specigying layout as a list
        VertexArrayOpenGLImpl(const std::initializer_list<LayoutElement> &l_list);

        // default constructor
        VertexArrayOpenGLImpl();

        // default deconstructor
        virtual ~VertexArrayOpenGLImpl();

        /**
         * @brief binds buffer to GL context
         */
        virtual void bind() override;

        /**
         * @brief unbinds buffer from GL context
         */
        virtual void unbind() override;

        /**
         * @brief update the layout attributes
         * @param l_list list of layout attributes
         */
        virtual void setLayout(const std::vector<LayoutElement> &l_list) override;

        /**
         * @brief binds Layout to GL context
         */
        virtual void bindLayout() override;

        /**
         * @brief unbinds Layout from GL context
         */
        virtual void unbindLayout() override;
    };

}