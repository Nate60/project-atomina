#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "OAS/SysBase.hpp"
#include "OAS/System.hpp"
#include "OAS/attributes/AttrRenderable.hpp"
#include "core/ATMAContext.hpp"

namespace ATMA
{
    /**
     * System that implements render calls on all objects that can be rendered
     */
    class ATMA_API SysRenderer: public SysBase
    {
    public:
        // default constructor
        SysRenderer();

        // deconstructor
        virtual ~SysRenderer();

        /**
         * update internal members on an engine tick basis
         * @param l_dt the time since last update
         */
        virtual void update(const long long &l_dt) override;

        /**
         * event callback function where the system will changes
         * its behaviour or perform an action based on the event details
         * @param l_e details of the event
         */
        virtual void notify(const ObjectEventContext &l_e) override;
    protected:
        /**
         * adds object to the system
         * @param l_id id of the object
         * @returns if the operation was successful
         */
        bool addObject(const ObjectId &l_id) override;


        /**
         * removes object from the system
         * @param l_id id of the object
         * @returns if the operation was successful
         */
        virtual bool removeObject(const ObjectId &l_id) override;

        std::unordered_map<unsigned int, unsigned int> m_renderIDs{};

    };

}
