#pragma once
#include "../pch.hpp"
#include "../core/api.hpp"

namespace ATMA
{

    using StateTypeID = unsigned int;
    using EventTypeID = unsigned int;
    
    struct ATMA_API CallBackKey
	{
        EventTypeID eventTypeID;
		StateTypeID stateTypeID;


		bool operator==(const CallBackKey &other){
			return stateTypeID == other.stateTypeID && eventTypeID == other.eventTypeID;
		}	
	};

    bool operator==(const CallBackKey a, const CallBackKey b);


}

namespace std
{
	template <>
  	struct ATMA_API hash<ATMA::CallBackKey>
  	{
        std::size_t operator()(const ATMA::CallBackKey& k) const
        {
        using std::size_t;
        using std::hash;
        using std::string;

        // Compute individual hash values for first,
        // second and third and combine them using XOR
        // and bit shifting:

        return ((hash<unsigned int>()(k.stateTypeID)
                ^ (hash<unsigned int>()(k.eventTypeID) << 1)) >> 1);
        }
    };
}