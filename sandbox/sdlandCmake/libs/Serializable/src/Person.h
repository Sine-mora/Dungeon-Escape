#pragma once
#include "Serializable.h"

class Person : public ISerializable
{
public:
    Person(const std::string& strName = "Person", int nAge = 0, float fWeight = 0.0f);
    virtual ~Person();

    // ISerializable interface
    virtual size_t GetSize() const final;
    virtual void Serialize(uint8_t* dataOut) const final;
    virtual void Deserialize(const uint8_t* dataIn) final;

    void Print();

private:
    std::string m_strName;
    int   m_nAge;
    float m_fWeight;
};