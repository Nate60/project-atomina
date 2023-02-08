#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "util/Props.hpp"

namespace ATMA
{

    class ATMA_API Window
    {
    public:
        Window(const std::string &l_name = "ATMA_APP");

        Window(const Props &l_props, const std::string &l_name = "ATMA_APP");

        virtual void setInputCallback(std::function<void(Window *, int, int, int, int)> l_callback
        ) = 0;

        virtual void swapBuffers() = 0;

        virtual void pollEvents() = 0;

        virtual void focus() = 0;

        virtual void setWindowShouldClose(bool l_bool) = 0;

        virtual bool getWindowShouldClose() const = 0;

        const std::string m_name;
    protected:
        Props m_props;
    };

}