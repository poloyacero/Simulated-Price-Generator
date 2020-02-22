#include "StreamQueue.hpp"

StreamQueue::StreamQueue(LogFile& log) {
	this->_log = &log;
}

void StreamQueue::pushStreams(Payload stream) {
	_streamQue.push(stream);
	this->monitor();
}

void StreamQueue::broadcast() {
	this->popStreams();
}

void StreamQueue::monitor() {
	if (this->checkQue()) {
		this->broadcast();
	}
}

bool StreamQueue::checkQue() {
	if (_streamQue.size() >= 5) {
		return true;
	} else {
		return false;
	}
}

void StreamQueue::popStreams() {
	while (!_streamQue.empty() && _streamQue.size() > 5) {
		this->_log->sharedLog(_streamQue.front());
		_streamQue.pop();
	}
}