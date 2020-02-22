#pragma once

#include <assert.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <cstdlib>
#include <ctime>
#include "StreamQueue.hpp"
#include "Payload.hpp"

#define PRICE_MIN_VALUE 0.75
#define PRICE_MAX_VALUE 1.25
#define PRICE_MIN_INCREMENT -0.00005
#define PRICE_MAX_INCREMENT 0.00005
#define TIME_MIN_INTERVAL 20
#define TIME_MAX_INTERVAL 5000

class PriceStream {
public:
	StreamQueue* _streamQue;
	Payload _payload;
	PriceStream(int random, StreamQueue& queue);
	void operator()(int threadID);
	void run(int id);
	float randomValue(float min, float max);
	void getValue();
	float getIncrement();
	void setIncrement(float increment);
private:
	float _price;
	float _increment;
	int _timeInterval;
};