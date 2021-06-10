#include "Person.h"

Person::Person(const std::string& strName, int nAge, float fWeight)
    : ISerializable(), m_strName{strName}, m_nAge{nAge}, m_fWeight{fWeight}
{
}

Person::~Person()
{
}

size_t Person::GetSize() const
{
    return  SerializablePOD<std::string>::GetSize(m_strName) +
            SerializablePOD<int>::GetSize(m_nAge) +
            SerializablePOD<float>::GetSize(m_fWeight);
}

void Person::Serialize(char* dataOut) const
{
    dataOut = SerializablePOD<std::string>::Serialize(dataOut, m_strName);
    dataOut = SerializablePOD<int>::Serialize(dataOut, m_nAge);
    dataOut = SerializablePOD<float>::Serialize(dataOut, m_fWeight);
}

void Person::Deserialize(const char* dataIn)
{
    dataIn = SerializablePOD<std::string>::Deserialize(dataIn, m_strName);
    dataIn = SerializablePOD<int>::Deserialize(dataIn, m_nAge);
    dataIn = SerializablePOD<float>::Deserialize(dataIn, m_fWeight);
}

void Person::Print()
{
    std::cout  << " name: " << m_strName << ", name_length: " << m_strName.length() << ", age: " << m_nAge << ", weight: " << m_fWeight << "\n";
}