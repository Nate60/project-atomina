#pragma once
#include "pch.hpp"
#include "core/ATMAContext.hpp"
#include "util/ATConst.hpp"
#include "AttrBase.hpp"

namespace ATMA
{

    using ObjectID = unsigned int;
    using AttrTypeID = unsigned int;
    using ObjectAttributes =
        std::pair<std::bitset<ATConst::OBJECT_BIT_SIZE>, std::unordered_map<AttrTypeID, std::shared_ptr<AttrBase>>>;
    using ObjectContainer = std::unordered_map<ObjectID, ObjectAttributes>;
    using AttributeFactory = std::unordered_map<AttrTypeID, std::function<std::shared_ptr<AttrBase>(void)>>;

    class AttributeManager
    {
    public:
        AttributeManager();
        virtual ~AttributeManager();

        /**
         * Assigns an Attribute class type to an unsigned integer id
         * @tparam class type to assign id to
         * @param l_attrType id to assign class type to
         * @throws RegistrationException if the id has a type already assigned
         */
        template<class T>
        void registerAttributeType(const unsigned int &l_attrType)
        {
            auto itr = m_attrFactory.find(l_attrType);
            if(itr != m_attrFactory.end())
            {
                throw RegistrationException(
                    "Attribute type: " + std::to_string(l_attrType) + " has already been registered"
                );
            }
            else
            {
                m_attrFactory[l_attrType] = []() -> std::shared_ptr<AttrBase> { return std::make_shared<T>(); };
                ATMA_ENGINE_INFO("Registered Attribute of type {0:d}", l_attrType);
            }
        }

        /**
         * allocates an unique id for a new object but does not assign any attributes to
         * it
         * @returns id of the new object
         */
        [[nodiscard]] unsigned int createObject(ATMAContext &l_ctx);

        /**
         * allocates an unique id for a new object and creates the corresponding attributes listing
         * in the given bit set
         * @param l_bits
         * @returns id of the new object
         */
        [[nodiscard]] unsigned int
        createObject(ATMAContext &l_ctx, const std::bitset<ATConst::OBJECT_BIT_SIZE> &l_bits);

        /**
         * Adds an attribute of the given id type to the given id
         * @param l_objectID object id to add attribute to
         * @param l_attrType id type of the attribute
         * @throws ValueNotFound Exception if either the object id or attribute type is not
         * registered to the context
         */
        void addAttribute(ATMAContext &l_ctx, const unsigned int &l_objectID, const unsigned int &l_attrType);

        /**
         * Removes an attribute of the given type from the specified object
         * @param l_objectID object id to remove the attribute from
         * @param l_attrType type id of the attribute to remove
         * @throws ValueNotFound Exception if either the object id or attribute type is not
         * registered to the context or if the object does not have the attribute
         */

        void removeAttribute(ATMAContext &l_ctx, const unsigned int &l_objectID, const unsigned int &l_attrType);

        /** checks if the object id has the given attribute
         * @param l_objectID id of the object to check
         * @param l_attrType type id to check for
         * @returns if the attribute was found or not
         */
        [[nodiscard]] bool hasAttribute(const unsigned int &l_objectID, const unsigned int &l_attrType);

        /**
         * gets a pointer to the specified attribute from the given object
         * @tparam type class of the attribute
         * @param l_objectID id of the object to get attribute from
         * @param l_attrType type id of the attribute to grab
         * @returns pointer to the attribute
         * @throws ValueNotFound Exception if object or attribute cannot be found in the context
         */
        template<class T>
        [[nodiscard]] std::shared_ptr<T> getAttribute(const unsigned int &l_objectID, const unsigned int &l_attrType)
        {
            auto itr = m_objects.find(l_objectID);
            if(itr == m_objects.end())
            {
                throw ValueNotFoundException(
                    "object id: " + std::to_string(l_objectID) + " does not contain any attributes or does not exist"
                );
            }
            else
            {
                auto innerItr = itr->second.second.find(l_attrType);
                if(innerItr == itr->second.second.end())
                {
                    throw ValueNotFoundException(
                        "object id: " + std::to_string(l_objectID)
                        + " does not contain attribute type: " + std::to_string(l_attrType)
                    );
                }
                else
                {
                    return std::dynamic_pointer_cast<T>(innerItr->second);
                }
            }
        }

        /**
         * removes all objects and attributes and resets the next id back to 0
         */
        void purge(ATMAContext &l_ctx);

        friend class SystemManager;
    protected:
        std::mutex m_mtx;
        ObjectID m_lastObjectID{0u};
        AttributeFactory m_attrFactory{};
        ObjectContainer m_objects{};
    };

}
