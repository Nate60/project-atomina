#pragma once
#include "pch.hpp"
#include "core/api.hpp"

namespace ATMA
{

    /**
     * @brief stores information based on the order of vertices for a draw call
     */
    class ATMA_API IndexBuffer
    {
    public:
        // constructor specifying the data in the buffer
        IndexBuffer(const std::vector<unsigned int> &l_data);

        // default deconstructor
        virtual ~IndexBuffer();

        /**
         * @brief update the internal data of the buffer
         * @param l_data new data
         */
        virtual void setBuffer(const std::vector<unsigned int> &l_data) = 0;

        /**
         * @brief factory function to create buffer with data
         * @param l_data interal data
         * @return new buffer pointer of the pre-determined implemenation type
         */
        static std::shared_ptr<IndexBuffer> makeBuffer(const std::vector<unsigned int> &l_data);

        /**
         * @brief factory function to create empty buffer
         * @return new buffer pointer of the pre-determined implementation type
         */
        static std::shared_ptr<IndexBuffer> makeBuffer();

        /**
         * @brief binds buffer to GL context
         */
        virtual void bind() = 0;

        /**
         * @brief unbinds buffer from GL context
         */
        virtual void unbind() = 0;
    protected:
        // default constructor
        IndexBuffer();
        std::vector<unsigned int> m_data;
        unsigned int m_bindID;
    };

    /**
     * @brief buffer specifying vertex data for draw calls
     */
    class ATMA_API VertexBuffer
    {
    public:
        // constructor specifying internal data
        VertexBuffer(const std::vector<float> &l_data);

        // default deconstructor
        virtual ~VertexBuffer();

        /**
         * @brief sets the internal data of the buffer
         * @param l_data data to set to
         */
        virtual void setBuffer(const std::vector<float> &l_data) = 0;

        /**
         * @brief factory function to create buffer with data
         * @param l_data interal data
         * @return new buffer pointer of the pre-determined implemenation type
         */
        static std::shared_ptr<VertexBuffer> makeBuffer(const std::vector<float> &l_data);

        /**
         * @brief factory function to create empty buffer
         * @return new buffer pointer of the pre-determined implementation type
         */
        static std::shared_ptr<VertexBuffer> makeBuffer();

        /**
         * @brief binds buffer to GL context
         */
        virtual void bind() = 0;

        /**
         * @brief unbinds buffer from GL context
         */
        virtual void unbind() = 0;
    protected:
        // default constructor
        VertexBuffer();
        std::vector<float> m_data;
        unsigned int m_bindID;
    };

    class ATMA_API VertexArray
    {
    public:
        /**
         * @brief Contains Vertex Attribute data for a vertex buffer
         */
        struct LayoutElement
        {
            unsigned int m_vertCount = 0, m_stride = 0, m_offset = 0;
        };

        // constructor specifying internal buffer data
        VertexArray(const std::vector<LayoutElement> &l_list);

        // constructor specifying interal buffer data as initializer list
        VertexArray(const std::initializer_list<LayoutElement> &l_list);

        // default deconstructor
        virtual ~VertexArray();

        /**
         * @brief update the layout attributes
         * @param l_list list of layout attributes
         */
        virtual void setLayout(const std::vector<LayoutElement> &l_list) = 0;

        /**
         * @brief factory function to create buffer with data
         * @param l_data interal data
         * @return new buffer pointer of the pre-determined implemenation type
         */
        static std::shared_ptr<VertexArray> makeBuffer(const std::vector<LayoutElement> &l_list);

        /**
         * @brief factory function to create buffer with data
         * @param l_data interal data
         * @return new buffer pointer of the pre-determined implemenation type
         */
        static std::shared_ptr<VertexArray>
        makeBuffer(const std::initializer_list<LayoutElement> &l_list);

        /**
         * @brief factory function to create empty buffer
         * @return new buffer pointer of the pre-determined implementation type
         */
        static std::shared_ptr<VertexArray> makeBuffer();

        /**
         * @brief binds buffer to GL context
         */
        virtual void bind() = 0;

        /**
         * @brief unbinds buffer from GL context
         */
        virtual void unbind() = 0;

        /**
         * @brief binds Layout to GL context
         */
        virtual void bindLayout() = 0;

        /**
         * @brief unbinds Layout from GL context
         */
        virtual void unbindLayout() = 0;
    protected:
        // default constructor
        VertexArray();
        unsigned int m_bindID;
        std::vector<LayoutElement> m_elementSpecs;
    };

}