#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "OAS/AttrBase.hpp"
#include "render/Buffer.hpp"
#include "render/ShaderProgram.hpp"

namespace ATMA
{

    class ATMA_API AttrRenderable: public AttrBase
    {
    public:
        // default constructor
        AttrRenderable();

        // deconstructor
        virtual ~AttrRenderable();

        // friend function to output attributes
        friend std::stringstream &operator>>(std::stringstream &l_stream, AttrBase &b);

        /**
         * fill attribute members with data contained within a string stream
         * @param l_stream string stream containing data of the attribute members
         */
        void readIn(std::stringstream &l_stream);

        unsigned int m_vertShader;
        unsigned int m_fragShader;
        std::shared_ptr<VertexArray> m_vertArray = VertexArray::makeBuffer();
        std::shared_ptr<VertexBuffer> m_vertBuffer = VertexBuffer::makeBuffer();
        std::shared_ptr<IndexBuffer> m_indexBuffer = IndexBuffer::makeBuffer();
        std::shared_ptr<ShaderProgram> m_shaderProg = ShaderProgram::makeProgram();
        bool m_doRender = true;
    };

}