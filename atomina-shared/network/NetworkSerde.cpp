#include "pch.hpp"
#include "NetworkSerde.hpp"

namespace ATMA
{
    const NetworkMessage NetworkSerde::deserialize(const std::vector<unsigned char> &l_bytes)
    {
        unsigned short advance = 0;
        // skip byte size header
        advance += sizeof(unsigned short);
        // determine message type
        unsigned int messageType;
        std::copy(
            l_bytes.begin() + advance,
            l_bytes.begin() + advance + sizeof(unsigned int),
            reinterpret_cast<unsigned char *>(&messageType)
        );
        advance += sizeof(unsigned int);
        Props p{};
        while(l_bytes[advance] != '\0')
        {
            // get value name
            std::string key = "";
            for(char c = l_bytes[advance]; c != '\0'; c = l_bytes[advance])
            {
                key += c;
                advance++;
            }
            // skip string terminator and value type so we can start at first byte in value
            advance += 2;
            switch(static_cast<NetworkMessageValueEnum>(l_bytes[advance - 1]))
            {
            case NetworkMessageValueEnum::CHAR:
                p[key] = (char)l_bytes[advance];
                advance++;
                break;
            case NetworkMessageValueEnum::UNSIGNEDCHAR:
                p[key] = l_bytes[advance];
                advance++;
                break;
            case NetworkMessageValueEnum::SHORT:
                {
                    short s;
                    std::copy(
                        l_bytes.begin() + advance,
                        l_bytes.begin() + advance + sizeof(short),
                        reinterpret_cast<unsigned char *>(&s)
                    );
                    advance += sizeof(short);
                    p[key] = s;
                }
                break;
            case NetworkMessageValueEnum::UNSIGNEDSHORT:
                {
                    unsigned short s;
                    std::copy(
                        l_bytes.begin() + advance,
                        l_bytes.begin() + advance + sizeof(unsigned short),
                        reinterpret_cast<unsigned char *>(&s)
                    );
                    advance += sizeof(unsigned short);
                    p[key] = s;
                }
                break;
            case NetworkMessageValueEnum::INT:
                {
                    int n;
                    std::copy(
                        l_bytes.begin() + advance,
                        l_bytes.begin() + advance + sizeof(int),
                        reinterpret_cast<unsigned char *>(&n)
                    );
                    advance += sizeof(int);
                    p[key] = n;
                }
                break;
            case NetworkMessageValueEnum::UNSIGNEDINT:
                {
                    unsigned int n;
                    std::copy(
                        l_bytes.begin() + advance,
                        l_bytes.begin() + advance + sizeof(unsigned int),
                        reinterpret_cast<unsigned char *>(&n)
                    );
                    advance += sizeof(unsigned int);
                    p[key] = n;
                }
                break;
            case NetworkMessageValueEnum::FLOAT:
                {
                    float f;
                    std::copy(
                        l_bytes.begin() + advance,
                        l_bytes.begin() + advance + sizeof(float),
                        reinterpret_cast<unsigned char *>(&f)
                    );
                    advance += sizeof(float);
                    p[key] = f;
                }
                break;
            case NetworkMessageValueEnum::LONG:
                {
                    long l;
                    std::copy(
                        l_bytes.begin() + advance,
                        l_bytes.begin() + advance + sizeof(long),
                        reinterpret_cast<unsigned char *>(&l)
                    );
                    advance += sizeof(long);
                    p[key] = l;
                }
                break;
            case NetworkMessageValueEnum::UNSIGNEDLONG:
                {
                    unsigned long l;
                    std::copy(
                        l_bytes.begin() + advance,
                        l_bytes.begin() + advance + sizeof(unsigned long),
                        reinterpret_cast<unsigned char *>(&l)
                    );
                    advance += sizeof(unsigned long);
                    p[key] = l;
                }
                break;
            case NetworkMessageValueEnum::DOUBLE:
                {
                    double d;
                    std::copy(
                        l_bytes.begin() + advance,
                        l_bytes.begin() + advance + sizeof(double),
                        reinterpret_cast<unsigned char *>(&d)
                    );
                    advance += sizeof(double);
                    p[key] = d;
                }
                break;
            case NetworkMessageValueEnum::LONGLONG:
                {
                    long long l;
                    std::copy(
                        l_bytes.begin() + advance,
                        l_bytes.begin() + advance + sizeof(long long),
                        reinterpret_cast<unsigned char *>(&l)
                    );
                    advance += sizeof(long long);
                    p[key] = l;
                }
                break;
            case NetworkMessageValueEnum::UNSIGNEDLONGLONG:
                {
                    unsigned long long l;
                    std::copy(
                        l_bytes.begin() + advance,
                        l_bytes.begin() + advance + sizeof(unsigned long long),
                        reinterpret_cast<unsigned char *>(&l)
                    );
                    advance += sizeof(unsigned long long);
                    p[key] = l;
                }
                break;
            case NetworkMessageValueEnum::STRING:
                {
                    std::string s{};
                    for(char c = l_bytes[advance]; c != '\0'; c = l_bytes[advance])
                    {
                        s += c;
                        advance++;
                    }
                    advance++;
                    p[key] = s;
                }
                break;
            default:
                throw ATMA::SerializationException("type not supported for deserialization");
            }
        }
        return NetworkMessage{messageType, p};
    }

    const std::vector<unsigned char> NetworkSerde::serialize(const NetworkMessage &l_message)
    {
        std::vector<unsigned char> bytes{};
        bytes.reserve(l_message.m_values.size() * 16 + 6);
        //reserve space for byte size header
        unsigned short messageSize = 0;
        for(int i = 0; i < sizeof(messageSize); i++)
        {
            short shift = i * sizeof(unsigned char) * 8;
            bytes.emplace_back((messageSize >> shift) & 0xFF);
            messageSize++;
        }
        // get message type
        for(int i = 0; i < sizeof(l_message.m_type); i++)
        {
            short shift = i * sizeof(unsigned char) * 8;
            bytes.emplace_back((l_message.m_type >> shift) & 0xFF);
            messageSize++;
        }

        // get values of message properties
        for(const auto &p: l_message.m_values)
        {
            // property name first
            for(const auto &c: p.first)
            {
                bytes.emplace_back(c);
                messageSize++;
            }
            bytes.emplace_back('\0');
            messageSize++;
            // property value type
            auto valuePair = std::any_cast<std::pair<unsigned char, std::any>>(p.second);
            bytes.emplace_back(valuePair.first);
            messageSize++;
            switch(static_cast<NetworkMessageValueEnum>(valuePair.first))
            {
            case NetworkMessageValueEnum::CHAR:
                bytes.emplace_back(std::any_cast<char>(valuePair.second));
                messageSize++;
                break;
            case NetworkMessageValueEnum::UNSIGNEDCHAR:
                bytes.emplace_back(std::any_cast<unsigned char>(valuePair.second));
                messageSize++;
                break;
            case NetworkMessageValueEnum::SHORT:
                {
                    auto v = std::any_cast<short>(valuePair.second);
                    const unsigned char *b = reinterpret_cast<const unsigned char *>(&v);
                    for(int i = 0; i < sizeof(short); i++)
                    {
                        bytes.emplace_back(b[i]);
                        messageSize++;
                    }
                }
                break;
            case NetworkMessageValueEnum::UNSIGNEDSHORT:
                {
                    auto v = std::any_cast<unsigned short>(valuePair.second);
                    const unsigned char *b = reinterpret_cast<const unsigned char *>(&v);
                    for(int i = 0; i < sizeof(unsigned short); i++)
                    {
                        bytes.emplace_back(b[i]);
                        messageSize++;
                    }
                }
                break;
            case NetworkMessageValueEnum::INT:
                {
                    auto v = std::any_cast<int>(valuePair.second);
                    const unsigned char *b = reinterpret_cast<const unsigned char *>(&v);
                    for(int i = 0; i < sizeof(int); i++)
                    {
                        bytes.emplace_back(b[i]);
                        messageSize++;
                    }
                }
                break;
            case NetworkMessageValueEnum::UNSIGNEDINT:
                {
                    auto v = std::any_cast<unsigned int>(valuePair.second);
                    const unsigned char *b = reinterpret_cast<const unsigned char *>(&v);
                    for(int i = 0; i < sizeof(unsigned int); i++)
                    {
                        bytes.emplace_back(b[i]);
                        messageSize++;
                    }
                }
                break;
            case NetworkMessageValueEnum::FLOAT:
                {
                    auto v = std::any_cast<float>(valuePair.second);
                    const unsigned char *b = reinterpret_cast<const unsigned char *>(&v);
                    for(int i = 0; i < sizeof(float); i++)
                    {
                        bytes.emplace_back(b[i]);
                        messageSize++;
                    }
                }
                break;
            case NetworkMessageValueEnum::LONG:
                {
                    auto v = std::any_cast<long>(valuePair.second);
                    const unsigned char *b = reinterpret_cast<const unsigned char *>(&v);
                    for(int i = 0; i < sizeof(long); i++)
                    {
                        bytes.emplace_back(b[i]);
                        messageSize++;
                    }
                }
                break;
            case NetworkMessageValueEnum::UNSIGNEDLONG:
                {
                    auto v = std::any_cast<unsigned long>(valuePair.second);
                    const unsigned char *b = reinterpret_cast<const unsigned char *>(&v);
                    for(int i = 0; i < sizeof(unsigned long); i++)
                    {
                        bytes.emplace_back(b[i]);
                        messageSize++;
                    }
                }
                break;
            case NetworkMessageValueEnum::DOUBLE:
                {
                    auto v = std::any_cast<double>(valuePair.second);
                    const unsigned char *b = reinterpret_cast<const unsigned char *>(&v);
                    for(int i = 0; i < sizeof(double); i++)
                    {
                        bytes.emplace_back(b[i]);
                        messageSize++;
                    }
                }
                break;
            case NetworkMessageValueEnum::LONGLONG:
                {
                    auto v = std::any_cast<long long>(valuePair.second);
                    const unsigned char *b = reinterpret_cast<const unsigned char *>(&v);
                    for(int i = 0; i < sizeof(long long); i++)
                    {
                        bytes.emplace_back(b[i]);
                        messageSize++;
                    }
                }
                break;
            case NetworkMessageValueEnum::UNSIGNEDLONGLONG:
                {
                    auto v = std::any_cast<unsigned long long>(valuePair.second);
                    const unsigned char *b = reinterpret_cast<const unsigned char *>(&v);
                    for(int i = 0; i < sizeof(unsigned long long); i++)
                    {
                        bytes.emplace_back(b[i]);
                        messageSize++;
                    }
                }
                break;
            case NetworkMessageValueEnum::STRING:
                {
                    auto v = std::any_cast<std::string>(valuePair.second);
                    for(const auto &c: v)
                    {
                        bytes.emplace_back(c);
                        messageSize++;
                    }
                    bytes.emplace_back('\0');
                    messageSize++;
                }
                break;
            default:
                throw ATMA::SerializationException("type not supported for serialization");
            }
        }
        bytes.emplace_back('\0');
        messageSize++;
        //update message size
        for(int i = 0; i < sizeof(messageSize); i++)
        {
            short shift = i * sizeof(unsigned char) * 8;
            bytes[i] = (messageSize >> shift) & 0xFF;
        }
        return bytes;
    }

}