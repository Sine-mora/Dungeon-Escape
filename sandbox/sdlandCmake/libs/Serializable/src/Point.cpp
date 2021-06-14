#include <iostream>
#include "Point.h"

Point::Point(uint32_t x, uint32_t y) : ISerializable(), m_x{ x }, m_y{ y }{
	std::cout << x << ' ' << y << std::endl;
}

Point::~Point() {
}

size_t Point::GetSize() const
{
    return
        SerializablePOD<uint32_t>::GetSize(m_x) +
        SerializablePOD<uint32_t>::GetSize(m_y);
}

void Point::Serialize(uint8_t* dataOut) const
{
    dataOut = SerializablePOD<uint32_t>::Serialize(dataOut, m_x);
    dataOut = SerializablePOD<uint32_t>::Serialize(dataOut, m_y);
}

void Point::Deserialize(const uint8_t* dataIn)
{
    dataIn = SerializablePOD<uint32_t>::Deserialize(dataIn, m_x);
    dataIn = SerializablePOD<uint32_t>::Deserialize(dataIn, m_y);
}

void Point::Print()
{
    std::cout << "Print() x: " << m_x << ", y: " << m_y <<"\n";
}