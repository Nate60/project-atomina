#pragma once
#include "util/ATConst.hpp"
#include "core/api.hpp"
#include "event/ObjectEventContext.hpp"
#include "event/ObjectEventListener.hpp"
#include "util/ATConst.hpp"
#include "util/Log.hpp"
#include "core/ATMAContext.hpp"
#include "time/StopWatch.hpp"

namespace ATMA
{

    class ATMAContext;
    using SystemType = unsigned int;

    using ObjectId = unsigned int;

    /**
     * Super class for systems which implement the behaviours of
     * attributes for each object register in the context
     */
    class SysBase: public ObjectEventListener, public std::enable_shared_from_this<SysBase>
    {
    public:
        const std::string m_sysTypeName;

        // constructor with system type and type name
        SysBase(const SystemType &l_type, const std::string &l_typeName):
            m_type(l_type),
            m_sysTypeName(l_typeName)
        {
        }

        // destructor
        virtual ~SysBase() {}

        /**
         * gives the enumerator for the type of system
         * @returns type enum of the system
         */
        SystemType getType() const;

        /**
         * returns true if the bitset matches the required bitset completely
         * @param l_bits bitset of the object to see if it matches the requirements
         * @returns if the bitset matches the requirement of the system
         */
        bool match(const std::bitset<ATConst::OBJECT_BIT_SIZE> &l_bits) const;

        /**
         * updates all attributes of all the objects contained in the system
         * @param time time since last update
         */
        virtual void update(const long long &l_dt) = 0;

        friend class ATMAContext;
    protected:
        /**
         * adds object to the system
         * @param l_id id of the object
         * @returns if the operation was successful
         */
        bool addObject(const ObjectId &l_id);

        /**
         * checks if the object is registering in the system
         * @param l_id id of the object
         * @returns if the object is registered
         */
        bool hasObject(const ObjectId &l_id) const;

        /**
         * removes object from the system
         * @param l_id id of the object
         * @returns if the operation was successful
         */
        bool removeObject(const ObjectId &l_id);

        /**
         * interface function for event listeners
         * @param l_e event details
         */
        virtual void notify(const ObjectEventContext &l_e) = 0;

        /**
         * removes all objects
         */
        void purge();

        SystemType m_type;
        std::bitset<ATConst::OBJECT_BIT_SIZE> m_req;
        std::vector<ObjectId> m_objects;
        StopWatch m_stopwatch{};
    };

}