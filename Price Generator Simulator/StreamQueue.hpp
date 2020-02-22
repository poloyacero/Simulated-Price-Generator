#pragma once

#include <iostream>
#include <queue>
#include "LogFile.hpp"
#include <string>
#include "Payload.hpp"

class StreamQueue {
public:
	StreamQueue(LogFile& log);
	void pushStreams(Payload stream);
	void popStreams();
	void broadcast();
	bool checkQue();
	void monitor();
private:
	LogFile* _log;
	std::queue <Payload> _streamQue;
};