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
    virtual void Serialize(uint8_t* dataOut) const = 0;
    virtual void Deserialize(const uint8_t* dataIn) = 0;

    void WriteCString(char*& target, const std::string& source);
};

template <typename POD>
class SerializablePOD
{
public:
    static size_t GetSize(POD str);
    static uint8_t* Serialize(uint8_t* target, POD value);
    static const uint8_t* Deserialize(const uint8_t* source, POD& target);
    static void PrintVector(const std::vector<uint8_t>& vec);
};

template<>
size_t SerializablePOD<uint8_t*>::GetSize(uint8_t* str);

template<>
uint8_t* SerializablePOD<uint8_t*>::Serialize(uint8_t* target, uint8_t* value);

template<>
const uint8_t* SerializablePOD<uint8_t*>::Deserialize(const uint8_t* source, uint8_t*& target);

// Explicit instantiation of used types
extern template class SerializablePOD<std::string>;
extern template class SerializablePOD<uint8_t*>;
extern template class SerializablePOD<uint32_t>;
extern template class SerializablePOD<float>;