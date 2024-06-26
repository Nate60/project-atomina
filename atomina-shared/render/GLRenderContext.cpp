#include "pch.hpp"
#include "GLRenderContext.hpp"
#ifdef ATMA_OPENGL
#    ifdef __linux__
#        include "renderImpl/OpenGL/GLRenderContextOpenGLUnixImpl.hpp"
#        define __ATMAMAKEGLRENDERCTX()                                                            \
            return std::move(std::make_unique<GLRenderContextOpenGLUnixImpl>())
#    elif _WINDOWS
#        include "renderImpl/OpenGL/GLRenderContextOpenGLWinImpl.hpp"
#        define __ATMAMAKEGLRENDERCTX()                                                            \
            return std::move(std::make_unique<GLRenderContextOpenGLWinImpl>())
#    endif
#else
#    include "renderImpl/Dummy/GLRenderContextDummyImpl.hpp"
#    define __ATMAMAKEGLRENDERCTX() return std::move(std::make_unique<GLRenderContextDummyImpl>())
#endif

namespace ATMA
{

    GLRenderContext::GLRenderContext() {}

    GLRenderContext::~GLRenderContext() {}

    void GLRenderContext::setFont(const std::shared_ptr<Font> l_font)
    {
        m_font = l_font;
    }

    unsigned int GLRenderContext::add(std::shared_ptr<GLRenderable> l_element)
    {
        auto id = m_lastId;
        m_elementContainer[id] =  l_element;
        auto itr = m_elementByPriority.find(l_element->m_stackPos);
        if(itr == m_elementByPriority.end())
        {
            std::vector<unsigned int> priorityList{};
            priorityList.push_back(id);
            m_elementByPriority[l_element->m_stackPos] = std::move(priorityList);
        }
        else{
            m_elementByPriority[l_element->m_stackPos].push_back(id);
        }
        m_lastId++;
        return id;
    }

    bool GLRenderContext::remove(const unsigned int &l_id)
    {
        auto itr = m_elementContainer.find(l_id);
        if(itr != m_elementContainer.end())
        {
            unsigned int stackPos = itr->second->m_stackPos;
            auto idItr = m_elementByPriority.find(stackPos);
            if(idItr->second.size() > 1)
            {
                for(auto i = idItr->second.begin(); i != idItr->second.end(); i++)
                {
                    if(*i == l_id){
                        idItr->second.erase(i);
                    }
                }
            }
            else
            {
                m_elementByPriority.erase(idItr);
            }
        }
        return false;
    }

    std::unique_ptr<GLRenderContext> GLRenderContext::makeRenderContext()
    {
        __ATMAMAKEGLRENDERCTX();
    }

}