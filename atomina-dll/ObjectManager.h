#pragma once
#include "pch.h"
#include "ATConst.h"
#include "Attribute.h"
#include "AttrBase.h"
#include "AtominaException.h"
#include "api.h"
#include "Log.h"


namespace ATMA {

	class ATMA_API ObjectManager {
		using ObjectId = unsigned int;
		using ObjectAttributes = std::pair<std::bitset<ATConst::OBJECT_BIT_SIZE>, std::unordered_map<int,AttrBase*>>;
	public:

		//TODO: add Texture Manager 
		ObjectManager();
		~ObjectManager();

		/**
		* Increments the id of the objectmanager and creates attributes for each active bit in the given bitset
		* assigns attributes to the id in the object map and returns the new id
		*/
		int createObject(const std::bitset<ATConst::OBJECT_BIT_SIZE>&);

		/**
		* Increments the id of the objectmanager and returns the id
		* note that since no attributes were created the id does not yet exist in the object map
		*/
		int createObject();

		/**
		* removes the object and all attributes from the object map
		* only returns true if successful
		*/
		bool removeObject(const ObjectId& l_id);

		/**
		* Creates an attribute using the attribute factory and assigns it to given object id
		* returns true only if successful
		*/
		bool addAttribute(const ObjectId& l_id, const Attribute& l_attr);

		/**
		* Creates attribute factory for the given attribute enum and type associaton
		* note association persists in the attribute factory
		*/
		template<class T>
		void addAttributeType(const Attribute& l_attr) {
			//lambda to add factory function, allows correspondence of template and enum
			ATMA_ENGINE_INFO("Adding {0} to object manager", l_attr);
			attrFactory_[l_attr] = []()->AttrBase* { return new T(); };
		}

		/**
		* Gets the pointer to attribute of the given object and enum association
		* throws an ObjectNotFoundException when the object or attribute does not exist in the objects map
		*/
		template<class T>
		T* getAttribute(const ObjectId& l_id, const Attribute& l_attr) {
			if (objects_.count(l_id) <= 0) {
				throw ObjectNotFoundException(std::string("object with id: " + std::to_string(l_id) + " was not found").c_str());
			}
			if (!objects_[l_id].first[(int)l_attr]) {
				throw ObjectNotFoundException(std::string("object with id: " + std::to_string(l_id) + " does not contain attribute: " + std::to_string((int)l_attr)).c_str());
			}

			return (T*)objects_[l_id].second[(int)l_attr];

		}

		/**
		* removes and deletes an attribute from the object id
		* returns true only if succesful
		*/
		bool removeAttribute(const ObjectId& l_id, const Attribute& l_attr);
		
		/**
		* checks if the given object id has the given attribute
		*/
		bool hasAttribute(const ObjectId& l_id, const Attribute& l_attr);

		/**
		* Clears all objects, clears all factory functions, and sets lastId to 0
		*/
		void purge();

	private:
		
		std::mutex mtx_;
		ObjectId lastId_;
		std::unordered_map<ObjectId, ObjectAttributes> objects_;
		std::unordered_map<Attribute, std::function<AttrBase* (void)>> attrFactory_;
		

	};
}
