#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "render/GLBuffer.hpp"

namespace ATMA
{
    /**
     * @brief Dummy implementation of Index Buffer
     */
    class ATMA_API IndexBufferDummyImpl: public IndexBuffer
    {
    public:
        // constructor specifying the data in the buffer
        IndexBufferDummyImpl(const std::vector<unsigned int> &l_data);

        // default constructor
        IndexBufferDummyImpl();

        // default deconstructor
        virtual ~IndexBufferDummyImpl();

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
     * @brief Dummy implementation of Vertex Buffer
     */
    class ATMA_API VertexBufferDummyImpl: public VertexBuffer
    {
    public:
        // constructor specifying the data in the buffer
        VertexBufferDummyImpl(const std::vector<float> &l_data);

        // default constructor
        VertexBufferDummyImpl();

        // default deconstructor
        virtual ~VertexBufferDummyImpl();

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
     * @brief Dummy implementation of Vertex Array
     */
    class ATMA_API VertexArrayDummyImpl: public VertexArray
    {
    public:
        // constructor specifying layout as a vector
        VertexArrayDummyImpl(const std::vector<LayoutElement> &l_list);

        // constructor specigying layout as a list
        VertexArrayDummyImpl(const std::initializer_list<LayoutElement> &l_list);

        // default constructor
        VertexArrayDummyImpl();

        // default deconstructor
        virtual ~VertexArrayDummyImpl();

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