#pragma once
#include "pch.hpp"
#include "core/api.hpp"

namespace ATMA
{

	enum class ATMA_API KeyEnum
    {
        NUMPAD_ADD          = 0x6B,
        BACKSPACE	        = 0x08,
        BREAK	            = 0x03,
        CLEAR	            = 0x0C,
        NUMPAD_DECIMAL	    = 0x6E,
        NUMPAD_DIVIDE	    = 0x6F,
        ESCAPE	            = 0x1B,
        _0	                = 0x30,
        _1	                = 0x31,
        _2	                = 0x32,
        _3	                = 0x33,
        _4	                = 0x34,
        _5	                = 0x35,
        _6	                = 0x36,
        _7	                = 0x37,
        _8	                = 0x38,
        _9	                = 0x39,
        _A	                = 0x41,
        _B	                = 0x42,
        _C	                = 0x43,
        _D	                = 0x44,
        _E	                = 0x45,
        _F	                = 0x46,
        _G	                = 0x47,
        _H	                = 0x48,
        _I	                = 0x49,
        _J	                = 0x4A,
        _K	                = 0x4B,
        _L	                = 0x4C,
        _M	                = 0x4D,
        _N	                = 0x4E,
        _O	                = 0x4F,
        _P	                = 0x50,
        _Q	                = 0x51,
        _R	                = 0x52,
        _S	                = 0x53,
        _T	                = 0x54,
        _U	                = 0x55,
        _V	                = 0x56,
        _W	                = 0x57,
        _X	                = 0x58,
        _Y	                = 0x59,
        _Z	                = 0x5A,
        NUMPAD_MULTIPLY	    = 0x6A,
        NUMPAD0	            = 0x60,
        NUMPAD1	            = 0x61,
        NUMPAD2	            = 0x62,
        NUMPAD3	            = 0x63,
        NUMPAD4	            = 0x64,
        NUMPAD5	            = 0x65,
        NUMPAD6	            = 0x66,
        NUMPAD7	            = 0x67,
        NUMPAD8	            = 0x68,
        NUMPAD9	            = 0x69,
        PLAY	            = 0xFA,
        PROCESSKEY	        = 0xE5,
        RETURN	            = 0x0D,
        SELECT	            = 0x29,
        SEPARATOR	        = 0x6C,
        SPACE	            = 0x20,
        SUBTRACT	        = 0x6D,
        TAB	                = 0x09,
        CAPITAL         	= 0x14,
        _DELETE	            = 0x2E,
        DOWN	            = 0x28,
        END	                = 0x23,
        F1	                = 0x70,
        F10	                = 0x79,
        F11	                = 0x7A,
        F12	                = 0x7B,
        F13	                = 0x7C,
        F14	                = 0x7D,
        F15	                = 0x7E,
        F16	                = 0x7F,
        F17	                = 0x80,
        F18	                = 0x81,
        F19	                = 0x82,
        F2	                = 0x71,
        F20	                = 0x83,
        F21	                = 0x84,
        F22	                = 0x85,
        F23	                = 0x86,
        F24	                = 0x87,
        F3	                = 0x72,
        F4	                = 0x73,
        F5	                = 0x74,
        F6	                = 0x75,
        F7	                = 0x76,
        F8	                = 0x77,
        F9	                = 0x78,
        ICO_00	            = 0xE4,
        INSERT	            = 0x2D,
        LBUTTON	            = 0x01,
        LCONTROL	        = 0xA2,
        LEFT	            = 0x25,
        LMENU	            = 0xA4,
        LSHIFT	            = 0xA0,
        LWIN	            = 0x5B,
        NUMLOCK	            = 0x90,
        PAUSE	            = 0x13,
        PRINT	            = 0x2A,
        RCONTROL	        = 0xA3,
        RIGHT	            = 0x27,
        RMENU	            = 0xA5,
        RSHIFT	            = 0xA1,
        RWIN	            = 0x5C,
        SLEEP	            = 0x5F,
        SNAPSHOT	        = 0x2C,
        UP	                = 0x26,
    };

    class ATMA_API KeyCode
    {
    public:
        // constructor with name
        KeyCode(const KeyEnum &l_type): m_type(l_type) {}

        // conversion constructor
        KeyCode(const unsigned int &l_int): m_type(static_cast<KeyEnum>(l_int)) {}

        // conversion operator
        operator unsigned int()
        {
            return static_cast<unsigned int>(m_type);
        }
    private:
        const KeyEnum m_type;
    };

}