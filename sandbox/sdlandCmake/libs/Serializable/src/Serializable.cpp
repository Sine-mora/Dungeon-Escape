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
size_t SerializablePOD<POD>::GetSize(POD str)
{
    return sizeof(POD);
}

template <typename POD>
char* SerializablePOD<POD>::Serialize(char* target, POD value)
{
    memcpy(target, &value, GetSize(value));
    target += GetSize(value);
    return target;
}

template <typename POD>
const char* SerializablePOD<POD>::Deserialize(const char* source, POD& target)
{
    memcpy(&target, source, GetSize(target));
    source += GetSize(target);
    return source;
}

template<>
size_t SerializablePOD<char*>::GetSize(char* str)
{
    return sizeof(size_t) + strlen(str) + 1;
}

template<>
char* SerializablePOD<char*>::Serialize(char* target, char* value)
{
    size_t length = strlen(value) + 1;
    target = SerializablePOD<size_t>::Serialize(target, length);
	value[length] = '\0';
    memcpy(target, value, length);
    target += length;
    return target;
}

template<>
const char* SerializablePOD<char*>::Deserialize(const char* source, char*& target)
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
char* SerializablePOD<std::string>::Serialize(char* target, std::string value)
{
    size_t length = value.length();
    target = SerializablePOD<size_t>::Serialize(target, length);
    memcpy(target, value.c_str(), length);
    target += length;
    return target;
}

template<>
const char* SerializablePOD<std::string>::Deserialize(const char* source, std::string& target)
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
template class SerializablePOD<char*>;
template class SerializablePOD<int>;
template class SerializablePOD<float>;