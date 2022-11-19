#pragma once
#include "util/ATConst.hpp"
#include "core/api.hpp"
#include "event/ObjectEventContext.hpp"
#include "event/ObjectEventListener.hpp"
#include "util/ATConst.hpp"
#include "util/Log.hpp"
#include "core/ATMAContext.hpp"

namespace ATMA
{

    class ATMAContext;
    using SystemType = unsigned int;

    using ObjectId = unsigned int;

    class ATMA_API SysBase: public ObjectEventListener
    {
    public:
        SysBase(const SystemType &l_type): m_type(l_type) {}

        virtual ~SysBase() {}

        /**
         * gives the enumerator for the type of system
         */
        SystemType getType() const;

        /**
         * returns true if the bitset matches the required bitset completely
         */
        bool match(const std::bitset<ATConst::OBJECT_BIT_SIZE> &l_bits) const;

        /**
         * updates all attributes of all the objects contained in the system
         */
        virtual void update(const float &l_dt) = 0;

        friend class ATMAContext;
    protected:
        /**
         * adds object to the system, returns true only if successful
         */
        bool addObject(const ObjectId &l_id);

        /**
         * returns if object is in the system or not
         */
        bool hasObject(const ObjectId &l_id) const;

        /**
         * removes object from the system, returns true only if succesful
         */
        bool removeObject(const ObjectId &l_id);

        virtual void notify(const ObjectEventContext &l_e) = 0;

        /**
         * removes all objects
         */
        void purge();

        SystemType m_type;
        std::bitset<ATConst::OBJECT_BIT_SIZE> m_req;
        std::vector<ObjectId> m_objects;
    };

}