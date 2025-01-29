#include "pch.hpp"
#include "NetworkSerde.hpp"

namespace ATMA
{
    const NetworkMessage NetworkSerde::deserialize(const std::vector<unsigned char> &l_bytes, size_t &l_amountUsed)
    {
        l_amountUsed = 0;
        ATMA_ENGINE_TRACE("deserializing message with {} bytes", l_bytes.size());
        // skip byte size header
        l_amountUsed += sizeof(unsigned short);
        // determine message type
        unsigned int messageType;
        // need to check we are not going out of bounds
        if(l_bytes.size() <= l_amountUsed + sizeof(unsigned int))
        {
            ATMA_ENGINE_WARN("encountered malformed message stream, too small");
            return NetworkMessage{NetworkMessageType(NetworkMessageEnum::INVALID)};
        }
        std::copy(
            l_bytes.begin() + l_amountUsed,
            l_bytes.begin() + l_amountUsed + sizeof(unsigned int),
            reinterpret_cast<unsigned char *>(&messageType)
        );
        l_amountUsed += sizeof(unsigned int);
        Props p{};
        while(l_bytes[l_amountUsed] != '\0')
        {
            // get value name
            std::string key = "";
            for(char c = l_bytes[l_amountUsed]; c != '\0'; c = l_bytes[l_amountUsed])
            {
                key += c;
                l_amountUsed++;
                if(l_bytes.size() <= l_amountUsed)
                {
                    ATMA_ENGINE_WARN("network message unexpected end of stream");
                    return NetworkMessage{NetworkMessageType(NetworkMessageEnum::INVALID)};
                }
            }
            // skip string terminator and value type so we can start at first byte in value
            l_amountUsed += 2;
            if(l_bytes.size() <= l_amountUsed)
            {
                ATMA_ENGINE_WARN("network message unexpected end of stream");
                return NetworkMessage{NetworkMessageType(NetworkMessageEnum::INVALID)};
            }
            switch(static_cast<NetworkMessageValueEnum>(l_bytes[l_amountUsed - 1]))
            {
            case NetworkMessageValueEnum::CHAR:
                p[key] = (char)l_bytes[l_amountUsed];
                l_amountUsed++;
                break;
            case NetworkMessageValueEnum::UNSIGNEDCHAR:
                p[key] = l_bytes[l_amountUsed];
                l_amountUsed++;
                break;
            case NetworkMessageValueEnum::SHORT:
                {
                    if(l_bytes.size() <= l_amountUsed + sizeof(short))
                    {
                        ATMA_ENGINE_WARN("network message unexpected end of stream");
                        return NetworkMessage{NetworkMessageType(NetworkMessageEnum::INVALID)};
                    }
                    short s;
                    std::copy(
                        l_bytes.begin() + l_amountUsed,
                        l_bytes.begin() + l_amountUsed + sizeof(short),
                        reinterpret_cast<unsigned char *>(&s)
                    );
                    l_amountUsed += sizeof(short);
                    p[key] = s;
                }
                break;
            case NetworkMessageValueEnum::UNSIGNEDSHORT:
                {
                    if(l_bytes.size() <= l_amountUsed + sizeof(unsigned short))
                    {
                        ATMA_ENGINE_WARN("network message unexpected end of stream");
                        return NetworkMessage{NetworkMessageType(NetworkMessageEnum::INVALID)};
                    }
                    unsigned short s;
                    std::copy(
                        l_bytes.begin() + l_amountUsed,
                        l_bytes.begin() + l_amountUsed + sizeof(unsigned short),
                        reinterpret_cast<unsigned char *>(&s)
                    );
                    l_amountUsed += sizeof(unsigned short);
                    p[key] = s;
                }
                break;
            case NetworkMessageValueEnum::INT:
                {
                    if(l_bytes.size() <= l_amountUsed + sizeof(int))
                    {
                        ATMA_ENGINE_WARN("network message unexpected end of stream");
                        return NetworkMessage{NetworkMessageType(NetworkMessageEnum::INVALID)};
                    }
                    int n;
                    std::copy(
                        l_bytes.begin() + l_amountUsed,
                        l_bytes.begin() + l_amountUsed + sizeof(int),
                        reinterpret_cast<unsigned char *>(&n)
                    );
                    l_amountUsed += sizeof(int);
                    p[key] = n;
                }
                break;
            case NetworkMessageValueEnum::UNSIGNEDINT:
                {
                    if(l_bytes.size() <= l_amountUsed + sizeof(unsigned int))
                    {
                        ATMA_ENGINE_WARN("network message unexpected end of stream");
                        return NetworkMessage{NetworkMessageType(NetworkMessageEnum::INVALID)};
                    }
                    unsigned int n;
                    std::copy(
                        l_bytes.begin() + l_amountUsed,
                        l_bytes.begin() + l_amountUsed + sizeof(unsigned int),
                        reinterpret_cast<unsigned char *>(&n)
                    );
                    l_amountUsed += sizeof(unsigned int);
                    p[key] = n;
                }
                break;
            case NetworkMessageValueEnum::FLOAT:
                {
                    if(l_bytes.size() <= l_amountUsed + sizeof(float))
                    {
                        ATMA_ENGINE_WARN("network message unexpected end of stream");
                        return NetworkMessage{NetworkMessageType(NetworkMessageEnum::INVALID)};
                    }
                    float f;
                    std::copy(
                        l_bytes.begin() + l_amountUsed,
                        l_bytes.begin() + l_amountUsed + sizeof(float),
                        reinterpret_cast<unsigned char *>(&f)
                    );
                    l_amountUsed += sizeof(float);
                    p[key] = f;
                }
                break;
            case NetworkMessageValueEnum::LONG:
                {
                    if(l_bytes.size() <= l_amountUsed + sizeof(long))
                    {
                        ATMA_ENGINE_WARN("network message unexpected end of stream");
                        return NetworkMessage{NetworkMessageType(NetworkMessageEnum::INVALID)};
                    }
                    long l;
                    std::copy(
                        l_bytes.begin() + l_amountUsed,
                        l_bytes.begin() + l_amountUsed + sizeof(long),
                        reinterpret_cast<unsigned char *>(&l)
                    );
                    l_amountUsed += sizeof(long);
                    p[key] = l;
                }
                break;
            case NetworkMessageValueEnum::UNSIGNEDLONG:
                {
                    if(l_bytes.size() <= l_amountUsed + sizeof(unsigned long))
                    {
                        ATMA_ENGINE_WARN("network message unexpected end of stream");
                        return NetworkMessage{NetworkMessageType(NetworkMessageEnum::INVALID)};
                    }
                    unsigned long l;
                    std::copy(
                        l_bytes.begin() + l_amountUsed,
                        l_bytes.begin() + l_amountUsed + sizeof(unsigned long),
                        reinterpret_cast<unsigned char *>(&l)
                    );
                    l_amountUsed += sizeof(unsigned long);
                    p[key] = l;
                }
                break;
            case NetworkMessageValueEnum::DOUBLE:
                {
                    if(l_bytes.size() <= l_amountUsed + sizeof(double))
                    {
                        ATMA_ENGINE_WARN("network message unexpected end of stream");
                        return NetworkMessage{NetworkMessageType(NetworkMessageEnum::INVALID)};
                    }
                    double d;
                    std::copy(
                        l_bytes.begin() + l_amountUsed,
                        l_bytes.begin() + l_amountUsed + sizeof(double),
                        reinterpret_cast<unsigned char *>(&d)
                    );
                    l_amountUsed += sizeof(double);
                    p[key] = d;
                }
                break;
            case NetworkMessageValueEnum::LONGLONG:
                {
                    if(l_bytes.size() <= l_amountUsed + sizeof(long long))
                    {
                        ATMA_ENGINE_WARN("network message unexpected end of stream");
                        return NetworkMessage{NetworkMessageType(NetworkMessageEnum::INVALID)};
                    }
                    long long l;
                    std::copy(
                        l_bytes.begin() + l_amountUsed,
                        l_bytes.begin() + l_amountUsed + sizeof(long long),
                        reinterpret_cast<unsigned char *>(&l)
                    );
                    l_amountUsed += sizeof(long long);
                    p[key] = l;
                }
                break;
            case NetworkMessageValueEnum::UNSIGNEDLONGLONG:
                {
                    if(l_bytes.size() <= l_amountUsed + sizeof(unsigned long long))
                    {
                        ATMA_ENGINE_WARN("network message unexpected end of stream");
                        return NetworkMessage{NetworkMessageType(NetworkMessageEnum::INVALID)};
                    }
                    unsigned long long l;
                    std::copy(
                        l_bytes.begin() + l_amountUsed,
                        l_bytes.begin() + l_amountUsed + sizeof(unsigned long long),
                        reinterpret_cast<unsigned char *>(&l)
                    );
                    l_amountUsed += sizeof(unsigned long long);
                    p[key] = l;
                }
                break;
            case NetworkMessageValueEnum::STRING:
                {
                    std::string s{};
                    for(char c = l_bytes[l_amountUsed]; c != '\0'; c = l_bytes[l_amountUsed])
                    {
                        s += c;
                        l_amountUsed++;
                        if(l_bytes.size() <= l_amountUsed)
                        {
                            ATMA_ENGINE_WARN("network message unexpected end of stream");
                            return NetworkMessage{NetworkMessageType(NetworkMessageEnum::INVALID)};
                        }
                    }
                    l_amountUsed++;
                    p[key] = s;
                }
                break;
            default:
                ATMA_ENGINE_WARN("unexpected network message value type");
                return NetworkMessage{NetworkMessageType(NetworkMessageEnum::INVALID)};
            }
            if(l_bytes.size() <= l_amountUsed)
            {
                ATMA_ENGINE_WARN("network message unexpected end of stream");
                return NetworkMessage{NetworkMessageType(NetworkMessageEnum::INVALID)};
            }
        }
        // we want cursor to point to index after last character used
        //  also this will make l_amountUsed equal to the bytestream of one entire message
        l_amountUsed++;
        return NetworkMessage{messageType, p};
    }

    const std::vector<unsigned char> NetworkSerde::serialize(const NetworkMessage &l_message)
    {
        std::vector<unsigned char> bytes{};
        bytes.reserve(l_message.values().size() * 16 + 6);
        // reserve space for byte size header
        unsigned short messageSize = 0;
        for(int i = 0; i < sizeof(messageSize); i++)
        {
            short shift = i * sizeof(unsigned char) * 8;
            bytes.emplace_back((messageSize >> shift) & 0xFF);
            messageSize++;
        }
        // get message type
        for(int i = 0; i < sizeof(l_message.type()); i++)
        {
            short shift = i * sizeof(unsigned char) * 8;
            bytes.emplace_back((l_message.type() >> shift) & 0xFF);
            messageSize++;
        }

        // get values of message properties
        for(const auto &p: l_message.values())
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
        // update message size
        for(int i = 0; i < sizeof(messageSize); i++)
        {
            short shift = i * sizeof(unsigned char) * 8;
            bytes[i] = (messageSize >> shift) & 0xFF;
        }
        return bytes;
    }

}