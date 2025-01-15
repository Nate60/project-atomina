#pragma once
#include <atomina.hpp>
#include "../GameEnums.hpp"

class AttrConnection: public ATMA::AttrBase
{
public:
    AttrConnection() : AttrBase(GameAttributeType(GameAttributeEnum::CONNECTION), "Connection")
    {
    }

    virtual ~AttrConnection()
    {
    }

    /**
     * fill attribute members with data contained within a string stream
     * @param l_stream string stream containing data of the attribute members
     */
    void readIn(std::stringstream &l_stream) override {}

    std::string m_name{};
    std::optional<unsigned int> m_id;
    std::mutex m_msgMutex;
    std::vector<ATMA::NetworkMessage> m_msgs{};

};