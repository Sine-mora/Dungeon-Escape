#include <iostream>
#include "Point.h"

Point::Point(int x, int y) : ISerializable(), m_x{ x }, m_y{ y }{
	std::cout << x << ' ' << y << std::endl;
}

Point::~Point() {
}

size_t Point::GetSize() const
{
    return
        SerializablePOD<int>::GetSize(m_x) +
        SerializablePOD<int>::GetSize(m_y);
}

void Point::Serialize(char* dataOut) const
{
    dataOut = SerializablePOD<int>::Serialize(dataOut, m_x);
    dataOut = SerializablePOD<int>::Serialize(dataOut, m_y);
}

void Point::Deserialize(const char* dataIn)
{
    dataIn = SerializablePOD<int>::Deserialize(dataIn, m_x);
    dataIn = SerializablePOD<int>::Deserialize(dataIn, m_y);

}

void Point::Print()
{
    std::cout << "Print() x: " << m_x << ", y: " << m_y <<"\n";
}