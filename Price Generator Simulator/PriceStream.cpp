#include "PriceStream.hpp"

std::mutex _mutex;
std::timed_mutex _tmutex;

PriceStream::PriceStream(int random, StreamQueue& queue) {
	this->_price = this->randomValue(PRICE_MIN_VALUE, PRICE_MAX_VALUE);
	this->_timeInterval = random;
	this->_streamQue = &queue;
}

void PriceStream::getValue() {
	std::cout << this->_price << '\n';
}

void PriceStream::setIncrement(float increment) {
	this->_increment = increment;
}

float PriceStream::getIncrement() {
	return (float)this->randomValue(PRICE_MIN_INCREMENT, PRICE_MAX_INCREMENT);
}

void PriceStream::operator()(int threadID) {
		this->run(threadID);
}

void PriceStream::run(int id) {
	while (true) {
		srand(time(0));
		
		std::unique_lock<std::mutex> locker(_mutex);

		this->_increment = this->getIncrement();
		this->_price += this->_increment;
		std::cout << "Thread: " << id << " - " << this->_price << " increment: " << this->_increment << " timestamp: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() << " interval: " << this->_timeInterval << '\n';
		this->_payload.setPayload(id + 1, this->_price, std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count());
		_streamQue->pushStreams(this->_payload);

		locker.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(this->_timeInterval));
	}
}

float PriceStream::randomValue(float min, float max) {
	assert(max > min);
	float random = ((float)rand()) / (float)RAND_MAX;
	float range = max - min;

	return (random * range) + min;
}

/*float PriceStream::randomIncrement(float min, float max) {
	assert(max > min);
	float random = ((float)rand()) / (float)RAND_MAX;
	float range = max - min;

	return (float)(random * range) + min;
}*/