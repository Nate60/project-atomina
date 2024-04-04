#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "util/Props.hpp"

namespace ATMA
{

    class AppWindow;
    /**
     * Enumerator for Possible App Window Events that can be created by
     * interacting with an App Window
     */
    enum class ATMA_API WindowEventEnum
    {
        None = 0,
        Close,
        Resize,
        COUNT
    };

    /**
     * Data Class for storing event data generated from an App Window Event abstracted
     * away from the operating specific implementations
     */
    class ATMA_API WindowEvent
    {
    public:
        // constructor for creating Window event with a window
        WindowEvent(const std::shared_ptr<AppWindow> l_win);

        // constructor with event type specified
        WindowEvent(const std::shared_ptr<AppWindow> l_win, const WindowEventEnum &l_eventType);

        // constructor with event type specificed and properties
        WindowEvent(
            const std::shared_ptr<AppWindow> l_win,
            const WindowEventEnum &l_eventType,
            const Props &l_props
        );

        // default constructor
        virtual ~WindowEvent();

        // copy constructor
        WindowEvent(const WindowEvent &l_other);

        // move constructor
        WindowEvent(WindowEvent &&l_other);

        // copy assignment operator
        WindowEvent &operator=(const WindowEvent &l_other) = default;

        // move assignment operator
        WindowEvent &operator=(WindowEvent &&l_other) = default;

        /**
         * property accessor function overloading accessor operator
         * @tparam type of value to be obtained
         * @param l_key key of value in properties map
         * @returns value as type from template
         */
        template<class T>
        const T &get(const std::string &l_key)
        {
            return m_props.getAs<T>(l_key);
        }

        const std::shared_ptr<AppWindow> m_win;
        const WindowEventEnum &m_type;
    protected:
        const Props m_props;
    };

    /**
     * Wrapper class for WindowEventEnum for conversion into unsigned int
     */
    class ATMA_API WindowEventType
    {
    public:
        // constructor for attribute type enum
        WindowEventType(const WindowEventEnum &l_type): m_type(l_type) {}

        // conversion constructor
        WindowEventType(const unsigned int &l_int): m_type(static_cast<WindowEventEnum>(l_int)) {}

        // conversion operator
        operator unsigned int()
        {
            return static_cast<unsigned int>(m_type);
        }
    protected:
        const WindowEventEnum m_type;
    };

}