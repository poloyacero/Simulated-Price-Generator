#include "PriceStream.hpp"
#include "LogFile.hpp"
#include "StreamQueue.hpp"
#include <iostream>
#include <thread>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>

#define NUMBER_OF_THREADS 5

float randomInterval(int min, int max) {
	float random = rand() / (float)RAND_MAX;
	float range = max - min;

	return (random * range) + min;
}

int main() {
	//srand( time(0));

	LogFile log;
	StreamQueue streamQ(log);

	std::cout << std::thread::hardware_concurrency() << '\n';
	std::vector<std::unique_ptr<PriceStream>> priceStream;
	std::thread threads[NUMBER_OF_THREADS];
	int randomNumber;
	
	for (int i = 0; i < NUMBER_OF_THREADS; i++) {
		randomNumber = (int)randomInterval(TIME_MIN_INTERVAL, TIME_MAX_INTERVAL);
		priceStream.push_back(std::make_unique<PriceStream>(randomNumber, std::ref(streamQ)));
		threads[i] = std::thread(*priceStream[i], i);
	}

	for (int i = 0; i < NUMBER_OF_THREADS; i++) {
		threads[i].join();
	}

	return 0;
}