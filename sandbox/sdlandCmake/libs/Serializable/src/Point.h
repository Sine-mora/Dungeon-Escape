#ifndef POINT_H
#define POINT_H
#include "Serializable/src/Serializable.h"

class Point : public ISerializable {
private:
	int m_x;
	int m_y;

public:
	Point(int x = 0, int y = 0);
	~Point();

	// ISerializable interface
	virtual size_t GetSize() const final;
	virtual void Serialize(char* dataOut) const final;
	virtual void Deserialize(const char* dataIn) final;
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
