#ifndef POINT_H
#define POINT_H
#include "Serializable.h"

class Point : public ISerializable {
private:
	uint32_t m_x;
	uint32_t m_y;

public:
	Point(uint32_t x = 0, uint32_t y = 0);
	~Point();

	// ISerializable interface
	virtual size_t GetSize() const final;
	virtual void Serialize(uint8_t* dataOut) const final;
	virtual void Deserialize(const uint8_t* dataIn) final;
	void Print();
	void SetPoint(int x, int y) {
		this->m_x = x;
		this->m_y = y;
	}
	
	int GetPointX() {
		return m_x;
	}

	int GetPointY() {
		return m_y;
	}

};

#endif // !POINT_H
