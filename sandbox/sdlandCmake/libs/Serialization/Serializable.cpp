#include <iostream>
#include <vector>
#include "Serializable.h"

Person::Person() : Serializable()
{
    
}

Person::Person(char* name, int age, float weight) : Serializable() {
    std::cout << "sadf";
}


size_t Person::serialize_size() const
{
     return SerializablePOD<char*>::serialize_size(m_name) +
         SerializablePOD<int>::serialize_size(m_age) +
         SerializablePOD<float>::serialize_size(m_weight);
}

void Person::serialize(char* dataOut) const
{
    dataOut = SerializablePOD<char*>::serialize(dataOut, m_name);
    dataOut = SerializablePOD<int>::serialize(dataOut, m_age);
    dataOut = SerializablePOD<float>::serialize(dataOut, m_weight);
}

void Person::deserialize(const char* dataIn)
{
    dataIn = SerializablePOD<char*>::deserialize(dataIn, m_name);
    dataIn = SerializablePOD<int>::deserialize(dataIn, m_age);
    dataIn = SerializablePOD<float>::deserialize(dataIn, m_weight);
}

template <typename POD>
size_t SerializablePOD<POD>::serialize_size(POD str)
{
    return sizeof(POD);
}

template  <typename POD>
char* SerializablePOD<POD>::serialize(char* target, POD value)
{
    return reinterpret_cast<char*>(std::memcpy(target, &value, serialize_size(value))); // returns void * to the last element (?)
}

template <typename POD>
const char* SerializablePOD<POD>::deserialize(const char* source, POD& target)
{
    std::memcpy(&target, source, serialize_size(target)); //copies the source to target with size()
    return source + serialize_size(target);          //returns the source + size
}


template<>
size_t SerializablePOD<char*>::serialize_size(char* str)
{
    //std::cout << sizeof(str) << ' ' << sizeof(char) * strlen(str) << ' ' << sizeof(size_t) + strlen(str) << std::endl;
    return sizeof(size_t) + strlen(str);
}

template<>
const char* SerializablePOD<char*>::deserialize(const char* source, char*& target)
{
    size_t length;
    memcpy(&length, source, sizeof(size_t));
    memcpy(&target, source + sizeof(size_t), length);
    return source + sizeof(size_t) + length;
}

//

template<> 
char* SerializablePOD<std::string>::serialize(char* target, std::string value)
{
    std::vector<char> bytes(value.begin(), value.end());
    bytes.push_back('\0');
    char* charArr = &bytes[0];
    return reinterpret_cast<char*>(std::memcpy(target, value.data(), value.length()));
}

template<>
size_t SerializablePOD<std::string>::serialize_size(std::string str) 
{
    std::cout << sizeof(char) * str.length() << ' ' << str.length() << ' ' << sizeof(size_t) + str.length() << std::endl;
    return str.length();
}

template<>
const char* SerializablePOD<std::string>::deserialize(const char* source, std::string& target) 
{
    size_t length;
    memcpy(&length, source, sizeof(size_t));                // razmer na string
    memcpy(&target, source + sizeof(size_t), length);         // sushtinski string
    return source + sizeof(size_t) + length;
}