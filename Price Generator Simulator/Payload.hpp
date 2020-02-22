#pragma once

#include <string>

class Payload {
public:
	void setPayload(int index, float price, __int64 timestamp);
	std::string getPayload();
private:
	int _index;
	float _price;
	__int64 _timestamp;
};