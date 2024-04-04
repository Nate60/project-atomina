#pragma once
#include "event/ObjectEventContext.hpp"
#include "pch.hpp"
#include "core/api.hpp"
#include "OAS/AttrBase.hpp"
#include "OAS/SysBase.hpp"
#include "resource/Resource.hpp"

namespace ATMA
{

    // functions for reading Atomina User Defined Types into the logger

    /**
     * converts an attribute to a stream with the details of the attribute appended to it
     * @param os stream to append the details to
     * @param a the attribute to read out
     * @returns the given stream with the details appended
     */
    ATMA_API std::ostream &operator<<(std::ostream &os, const std::shared_ptr<AttrBase> a);

    /**
     * converts a system to a stream with the details system appended to it
     * @param os stream to append the details to
     * @param s the system to read out
     * @returns the given stream with the details appended
     */
    ATMA_API std::ostream &operator<<(std::ostream &os, const std::shared_ptr<SysBase> s);

    /**
     * converts a resource to a stream with the details of the resource appended to it
     * @param os stream to append the details to
     * @param r the resource to read out
     * @returns the given stream with the details appended
     */
    ATMA_API std::ostream &operator<<(std::ostream &os, const std::shared_ptr<Resource> r);

    /**
     * converts an event to a stream with the details of the event appended to it
     * @param os stream to append the details to
     * @param e the event to read out
     * @returns the given stream with the details appended
     */
    ATMA_API std::ostream &operator<<(std::ostream &os, const ObjectEventContext &e);

    /**
     * converts an event to a stream with the details of the event appended to it
     * @param os stream to append the details to
     * @param e the event to read out
     * @returns the given stream with the details appended
     */
    ATMA_API std::ostream &operator<<(std::ostream &os, const std::shared_ptr<AppWindow> e);


}
