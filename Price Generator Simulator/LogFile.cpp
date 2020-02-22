#include "LogFile.hpp"

LogFile::LogFile() {
	this->_file.open("logfile.csv");
}

LogFile::~LogFile() {
	this->_file.close();
}

void LogFile::sharedLog(Payload payload) {
	std::thread([this, &payload]() {
		this->_file << payload.getPayload() << '\n';
	}).join();
}