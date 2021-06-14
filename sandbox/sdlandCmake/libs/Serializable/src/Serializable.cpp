#include "Serializable.h"

void ISerializable::WriteCString(char*& target, const std::string& source)
{
    if(target)
    {
        delete[] target;
        target = nullptr;
    }
    
    target = new char[source.length() + 1];
    memcpy(target, source.c_str(), source.length());
    target[source.length()]='\0';
}

template <typename POD>
void SerializablePOD<POD>::PrintVector(const std::vector<uint8_t>& vec) {
    std::cout << "Vec size : " << vec.size();
    uint32_t uintcounter = 0;
    for (const auto somebyte : vec) {
        std::cout << "byte[" << uintcounter << "] : " << static_cast<uint32_t>(somebyte) << '\n';
        uintcounter++;
    }

}
template <typename POD>
size_t SerializablePOD<POD>::GetSize(POD str)
{
    return sizeof(POD);
}
template <typename POD>
uint8_t* SerializablePOD<POD>::Serialize(uint8_t* target, POD value)
{
    memcpy(target, &value, GetSize(value));
    target += GetSize(value);
    return target;
}
template <typename POD>
const uint8_t* SerializablePOD<POD>::Deserialize(const uint8_t* source, POD& target)
{
    memcpy(&target, source, GetSize(target));
    source += GetSize(target);
    return source;
}
template<>
size_t SerializablePOD<uint8_t*>::GetSize(uint8_t* str)
{
    return sizeof(size_t) + sizeof(str) + 1;
}
template<>
uint8_t* SerializablePOD<uint8_t*>::Serialize(uint8_t* target, uint8_t* value)
{
    size_t length = sizeof(value) + 1;
    target = SerializablePOD<size_t>::Serialize(target, length);
	value[length] = '\0';
    memcpy(target, value, length);
    target += length;
    return target;
}
template<>
const uint8_t* SerializablePOD<uint8_t*>::Deserialize(const uint8_t* source, uint8_t*& target)
{
    size_t length;
    memcpy( &length, source, sizeof(size_t) );
    source += sizeof(size_t);
    memcpy( target, source, length);
    source += length;
    return source;
}
template<>
size_t SerializablePOD<std::string>::GetSize(std::string str)
{
    return sizeof(size_t) + str.length();
}
template<>
uint8_t* SerializablePOD<std::string>::Serialize(uint8_t* target, std::string value)
{
    size_t length = value.length();
    target = SerializablePOD<size_t>::Serialize(target, length);
    memcpy(target, value.c_str(), length);
    target += length;
    return target;
}
template<>
const uint8_t* SerializablePOD<std::string>::Deserialize(const uint8_t* source, std::string& target)
{
    size_t length;
    memcpy( &length, source, sizeof(size_t) );
    source += sizeof(size_t);
	
	std::vector<char> buff;
    buff.reserve(length);
    memcpy(buff.data(), source, length);
    source += length;
	target = std::string(buff.data(), length);
    return source;
}


// Explicit instantiation of used types
template class SerializablePOD<std::string>;
template class SerializablePOD<uint8_t*>;
template class SerializablePOD<uint32_t>;
template class SerializablePOD<float>;