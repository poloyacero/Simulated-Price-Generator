#include "Payload.hpp"

void Payload::setPayload(int index, float price, __int64 timestamp) {
	this->_index = index;
	this->_price = price;
	this->_timestamp = timestamp;
}

std::string Payload::getPayload() {
	std::string payload = "" + std::to_string(this->_index) + "," + std::to_string(this->_price) + "," + std::to_string(this->_timestamp) + "";
	return payload;
}