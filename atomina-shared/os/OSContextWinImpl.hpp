#ifdef _WINDOWS
#   pragma once
#   include "pch.hpp"
#   include "core/api.hpp"

namespace ATMA
{

    /**
     * Global Windows Context Singleton for handling DLL Instance Handle
     * needed for window creation on Windows systems
    */
    class ATMA_API OSContextWinImpl
    {
    public:
        //default deconstructor
        virtual ~OSContextWinImpl();

        //factory function for singleton
        static OSContextWinImpl &getContext()
        {
            static OSContextWinImpl context; // Guaranteed to be destroyed.
                                           // Instantiated on first use.
            return context;
        }

        /**
         * set Instance Handle for library DLL
         * @param l_dllHandle Instance handle for windows DLL
        */
        void setDLLInstanceHandle(const HINSTANCE &l_dllHandle);

        /**
         * getter for instance handle
         * @returns DLL instance handle
        */
        const HINSTANCE &getDLLInstanceHandle();
    protected:
        //protected default constructor used by factory
        OSContextWinImpl();
        HINSTANCE m_dllInstanceHandle;
    };

}
#else
#    error Windows implementation included in non-Windows target
#endif