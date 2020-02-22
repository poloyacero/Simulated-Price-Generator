#pragma once

#include <iostream>
#include <fstream>
#include <thread>
#include "Payload.hpp"

class LogFile {
public:
	LogFile();
	~LogFile();
	void sharedLog(Payload payload);
private:
	std::ofstream _file;
};