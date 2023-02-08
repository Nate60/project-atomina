#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "render/Buffer.hpp"

namespace ATMA
{
    /**
     * @brief OpenGL implementation of Index Buffer
     */
    class ATMA_API IndexBufferGLADImpl: public IndexBuffer
    {
    public:
        // constructor specifying the data in the buffer
        IndexBufferGLADImpl(const std::vector<unsigned int> &l_data);

        // default constructor
        IndexBufferGLADImpl();

        // default deconstructor
        virtual ~IndexBufferGLADImpl();

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
    class ATMA_API VertexBufferGLADImpl: public VertexBuffer
    {
    public:
        // constructor specifying the data in the buffer
        VertexBufferGLADImpl(const std::vector<float> &l_data);

        // default constructor
        VertexBufferGLADImpl();

        // default deconstructor
        virtual ~VertexBufferGLADImpl();

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
    class ATMA_API VertexArrayGLADImpl: public VertexArray
    {
    public:
        // constructor specifying layout as a vector
        VertexArrayGLADImpl(const std::vector<LayoutElement> &l_list);

        // constructor specigying layout as a list
        VertexArrayGLADImpl(const std::initializer_list<LayoutElement> &l_list);

        // default constructor
        VertexArrayGLADImpl();

        // default deconstructor
        virtual ~VertexArrayGLADImpl();

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