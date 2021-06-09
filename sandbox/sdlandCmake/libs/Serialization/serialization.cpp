#include <iostream>

// Interface class
class Serializable
{
public:
    virtual size_t serialize_size() const = 0;
    virtual void serialize(char* dataOut) const = 0;
    virtual void deserialize(const char* dataIn) = 0;
};

/// 

class SerialDeserial : public Serializable
{
public:
    virtual size_t serialize_size() const
    {
        return SerializablePOD<char*>::serialize_size(name) +
            SerializablePOD<int>::serialize_size(age) +
            SerializablePOD<float>::serialize_size(weight);
    }

    virtual void serialize(char* dataOut) const
    {
        dataOut = SerializablePOD<char*>::serialize(dataOut, name);
        dataOut = SerializablePOD<int>::serialize(dataOut, age);
        dataOut = SerializablePOD<float>::serialize(dataOut, weight);
    }

    virtual void deserialize(const char* dataIn)
    {
        dataIn = SerializablePOD<char*>::deserialize(dataIn, name);
        dataIn = SerializablePOD<int>::deserialize(dataIn, age);
        dataIn = SerializablePOD<float>::deserialize(dataIn, weight);
    }

private:
    char* m_name;
    int   m_age;
    float m_weight;

    Serializable& s;
    void m_reserve_memory(char*& data, size_t& data_len)
    {
        data_len = s.serialize_size();

        //return new char[s.serialize_size()];
    }
};

///

template <typename POD>
class SerializablePOD
{

public:

    static size_t serialize_size(POD str)
    {
        return sizeof(POD);
    }

    static char* serialize(char* target, POD value)
    {
        return std::memcpy(target, &value, serialize_size(value)); // returns void * to the last element (?)
    }

    static const char* deserialize(const char* source, POD& target)
    {
        std::memcpy(&target, source, serialize_size(target)); //copies the source to target with size()
        return source + serialize_size(target);          //returns the source + size
    }

};

template<>
size_t SerializablePOD<char*>::serialize_size(char* str)
{
    std::cout << sizeof(str) << ' ' << sizeof(char) * strlen(str) << ' ' << sizeof(size_t) + strlen(str) << std::endl;
    return sizeof(char) * strlen(str);
}

template<>
const char* SerializablePOD<char*>::deserialize(const char* source, char*& target)
{
    size_t length;
    memcpy(&length, source, sizeof(size_t));
    memcpy(&target, source + sizeof(size_t), length);
    return source + sizeof(size_t) + length;
}