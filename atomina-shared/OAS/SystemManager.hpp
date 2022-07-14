#pragma once
#include "../util/ATConst.hpp"
#include "../core/api.hpp"
#include "System.hpp"
#include "SysBase.hpp"
#include "ObjectManager.hpp"
#include "../util/AtominaException.hpp"
#include "../event/Event.hpp"
#include "../util/Log.hpp"

namespace ATMA {

	class SysBase;
	class ObjectManager;

	using ObjectId = unsigned int;

	class ATMA_API SystemManager {

	public:
		
		SystemManager();

		/**
		* Adds a System to system-class relation to the system manager
		*/
		template <class T>
		bool addSystem(const System &l_sys)
		{
			return addSystem<T>(static_cast<SystemType>(l_sys));
		}

		/**
		* Adds a System to system-class relation to the system manager
		*/
		template <class T>
		bool addSystem(const SystemType &l_sys) {
			if constexpr(std::is_base_of_v<SysBase, T>)
			{
				auto func = [=]()->std::shared_ptr<SysBase> { return std::shared_ptr<T>{new T(l_sys, *this)}; };
				if(m_systems.find(l_sys) == m_systems.end())
				{
					m_systems[l_sys] = func();
					ATMA_ENGINE_INFO("added system of type {0:d} to manager", l_sys);
					return true;
				}
				else
				{
					ATMA_ENGINE_WARN("unable system of type {0:d} to manager as it already exists", l_sys);
					return false;
				}
		
			}
			else
			{
				throw std::bad_cast{};
			}
		}


		/**
		* Gets a system from the system manager but throws exception if it does not exist
		*/
		template <class T>
		std::shared_ptr<T> getSystem(const System &l_sys)
		{
			return getSystem<T>(static_cast<SystemType>(l_sys));
		}
		/**
		* Gets a system from the system manager but throws exception if it does not exist
		*/
		template <class T>
		std::shared_ptr<T> getSystem(const SystemType &l_sys) {
			if constexpr(std::is_base_of_v<SysBase, T>)
			{
				if(m_systems.find(l_sys) == m_systems.end())
				{
					throw ValueNotFoundException("System type " + std::to_string(l_sys) + " does not exist");
				}
				return std::static_pointer_cast<T>(m_systems[l_sys]);
			}
			else
			{
				throw std::bad_cast{};
			}
		}


		//getter for object manager
		std::shared_ptr<ObjectManager> getObjectManager() {
			return m_objMan;
		}

		void addEvent(const ObjectId &l_object, Event &l_event);


		//updates all attributes of all systems
		void update(float l_dt);

		void handleEvents();

		//TODO window abstraction

		/**
		* To be called when an object loses or gains an attribute so that it can be added and removed
		* from the corresponding systems
		*/
		void objectModified(const ObjectId& l_id, const std::bitset<ATConst::OBJECT_BIT_SIZE> l_bits);
		
		/**
		* Removes object id from all systems
		*/
		void removeObject(const ObjectId& l_id);


		/**
		* removes all object Ids
		*/
		void purgeObjects();

		/**
		* removes all system-system class relations
		*/
		void purgeSystems();



	private:
		std::shared_ptr<ObjectManager> m_objMan;
		std::unordered_map<SystemType, std::shared_ptr<SysBase>> m_systems{};
		std::unordered_map<ObjectId, std::vector<Event>> m_object_event_queue{};

	};

}