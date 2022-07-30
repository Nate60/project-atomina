#pragma once
#include "api.hpp"
#include "../event/EventContext.hpp"
#include "../util/ATConst.hpp"
#include "../OAS/AttrBase.hpp"
#include "../OAS/SysBase.hpp"
#include "../state/BaseState.hpp"
#include "../event/CallBackKey.hpp"
#include "../util/Log.hpp"
#include "../util/AtominaException.hpp"

namespace ATMA
{

	using StateTypeID = unsigned int;
	using EventTypeID = unsigned int;



	class ATMAContext;
	class SysBase;
	class BaseState;


	using CallBackFunction = std::function<void(EventContext&)>;
	using CallBackRegistry = std::unordered_map<CallBackKey, CallBackFunction>;
	using EventQueue = std::vector<std::tuple<EventTypeID,StateTypeID,EventContext>>;

	using ObjectID = unsigned int;
	using AttrTypeID = unsigned int;
	using ObjectAttributes = std::pair<std::bitset<ATConst::OBJECT_BIT_SIZE>, std::unordered_map<AttrTypeID,std::shared_ptr<AttrBase>>>;
	using ObjectContainer = std::unordered_map<ObjectID, ObjectAttributes>;
	using AttributeFactory = std::unordered_map<AttrTypeID, std::function<std::shared_ptr<AttrBase>(void)>>;

	using SystemID = unsigned int;
	using SystemContainer = std::unordered_map<SystemID, std::unique_ptr<SysBase>>;

	using StateStack = std::unordered_map<StateTypeID,std::unique_ptr<BaseState>>;

	using ResourceID = unsigned int;
	using ResourceTypeID = unsigned int;
	using ResourceContainer = std::unordered_map<ResourceID, std::pair<ResourceTypeID, std::string>>;

	class ATMA_API ATMAContext
	{
	private:
		CallBackRegistry m_callbacks{};
		EventQueue m_eventQueue{};

		std::mutex m_mtx{};
		ObjectID m_lastId{0u};
		AttributeFactory m_attrFactory{};
		ObjectContainer m_objects{};

		SystemContainer m_systems{};

		StateTypeID m_currentStateID{};
		StateStack m_states{};

		ResourceContainer m_resources;

		ATMAContext()
		{
			ATMA_ENGINE_INFO("ATMAContext has been initialized");
		}

		//helper function
		void objectUpdated(const unsigned int &l_objectID, const std::bitset<ATConst::OBJECT_BIT_SIZE> &l_bits);
	public: 

		
		//get context
		static ATMAContext& getContext()
        {
            static ATMAContext context; // Guaranteed to be destroyed.
                                  // Instantiated on first use.
            return context;
        }

		ATMAContext(ATMAContext const&) = delete;
        void operator=(ATMAContext const&)  = delete;

		//add callback
		void addCallback(const unsigned int &l_eventType, const unsigned int &l_stateType, CallBackFunction l_func);

		//remove callback
		void removeCallback(const unsigned int &l_eventType, const unsigned int &l_stateType);

		//add event
		void addEvent(const unsigned int &l_eventType, const unsigned int &l_stateType, EventContext&& l_context);

		//add factory function
		template <class T>
		void registerAttributeType(const unsigned int &l_attrType)
		{
			auto itr = m_attrFactory.find(l_attrType);
			if(itr != m_attrFactory.end())
			{
				throw RegistrationException("Attribute type: " + std::to_string(l_attrType) + " has already been registered");
			}
			else{
				m_attrFactory[l_attrType] = []()->std::shared_ptr<AttrBase>{return std::shared_ptr<T>{new T{}};};
				ATMA_ENGINE_INFO("Registered Attribute of type {0:d}", l_attrType);
			}

		}

		[[nodiscard]] unsigned int createObject();

		[[nodiscard]] unsigned int createObject(const std::bitset<ATConst::OBJECT_BIT_SIZE> &l_bits);

		//add attribute
		void addAttribute(const unsigned int &l_objectID, const unsigned int &l_attrType);

		//remove attribute
		void removeAttribute(const unsigned int &l_objectID, const unsigned int &l_attrType);

		//check attribute
		bool hasAttribute(const unsigned int &l_objectID, const unsigned int &l_attrType);

		//get Attribute
		template<class T>
		std::shared_ptr<T> getAttribute(const unsigned int &l_objectID, const unsigned int &l_attrType)
		{
			auto itr = m_objects.find(l_objectID);
			if(itr == m_objects.end())
			{
				throw ValueNotFoundException("object id: " + std::to_string(l_objectID) + " does not contain any attributes or does not exist");
			}
			else 
			{
				auto innerItr = itr->second.second.find(l_attrType);
				if(innerItr == itr->second.second.end())
				{
					 throw ValueNotFoundException("object id: " + std::to_string(l_objectID) + " does not contain attribute type: " + std::to_string(l_attrType));
				}
				else
				{
					return std::dynamic_pointer_cast<T>(innerItr->second);
				}
			}
		}

		//add system
		void addSystem(const unsigned int &l_systemID, std::unique_ptr<SysBase> l_system);
		
		void disableSystem(const unsigned int &l_systemID);

		void enableSystem(const unsigned int &l_systemID);

		bool hasSystem(const unsigned int &l_systemID);

		//remove system
		void removeSystem(const unsigned int &l_systemID);

		//add state
		void addState(const unsigned int &l_stateType, std::unique_ptr<BaseState> l_state);

		//remove state
		void removeState(const unsigned int &l_stateType);

		//switch to state
		void switchToState(const unsigned int &l_stateType);

		//check state
		bool hasState(const unsigned int &l_stateType);

		//add resource

		//remove resource

		void update();

		void purgeObjects();

		void purgeSystems();

		void purgeStates();

		void purgeEvents();

		void purgeResources();

		void purge();

	};

}