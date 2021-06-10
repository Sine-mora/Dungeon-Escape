#pragma once
#include <cstdint>
#include <string>
#include <cstring>
#include <iostream>
#include <vector>


// Interface class
class ISerializable
{
public:
    virtual size_t GetSize() const = 0;
    virtual void Serialize(char* dataOut) const = 0;
    virtual void Deserialize(const char* dataIn) = 0;

    void WriteCString(char*& target, const std::string& source);
};

template <typename POD>
class SerializablePOD
{
public:
    static size_t GetSize(POD str);
    static char* Serialize(char* target, POD value);
    static const char* Deserialize(const char* source, POD& target);
};

template<>
size_t SerializablePOD<char*>::GetSize(char* str);

template<>
char* SerializablePOD<char*>::Serialize(char* target, char* value);

template<>
const char* SerializablePOD<char*>::Deserialize(const char* source, char*& target);

template<>
size_t SerializablePOD<std::string>::GetSize(std::string str);

template<>
char* SerializablePOD<std::string>::Serialize(char* target, std::string value);

template<>
const char* SerializablePOD<std::string>::Deserialize(const char* source, std::string& target);


// Explicit instantiation of used types
extern template class SerializablePOD<std::string>;
extern template class SerializablePOD<char*>;
extern template class SerializablePOD<int>;
extern template class SerializablePOD<float>;