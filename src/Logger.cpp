#include "Logger.hpp"

#include <cstdint>
#include <cstring>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif

Logger::TraceMessage BUFFER[BUFFER_SIZE];
unsigned int BUFFER_CPT = 0;

void Logger::flushTraces() {
	for (int i = 0; i < BUFFER_CPT; i++) {
		std::cout << to_string(BUFFER[i]) + "\n\r";
	}
	std::cout << std::flush;
	std::memset(BUFFER, 0, sizeof(BUFFER));
	BUFFER_CPT = 0;
}


Logger::TraceMessage::TraceMessage() {
	this->time = Logger::getCurrentTime();
	this->message = new char[0];
	strcpy(this->message, "");
	this->level = Logger::TraceLevels::Trace;
}

Logger::TraceMessage::TraceMessage(Logger::TraceLevels level, char* message) {
	this->time = getCurrentTime();
	this->message = new char[strlen(message)];
	strcpy(this->message, message);
	this->level = level;
}

void Logger::log(TraceLevels level, char* content) {
	log(Logger::TraceMessage(level, content));
}

void Logger::log(TraceLevels level, const char* content) {
	log(level, const_cast<char*>(content));
	
}

void Logger::log(TraceMessage message) {
	if (BUFFER_CPT <= BUFFER_SIZE) {
		BUFFER[BUFFER_CPT] = message;
		BUFFER_CPT++;
	} else {
		Logger::flushTraces();
	}
}

void Logger::flushAtExit() {
	Logger::flushTraces();
}

void Logger::initializeLogger() {
	Logger::log(Logger::TraceLevels::Info, "Initialize logger");
	std::atexit(Logger::flushAtExit);
}



std::string Logger::to_string(Logger::TraceMessage message) {
	return message.getTime() + to_string(message.getLevel()) + " - " + std::string(message.getMessage());
}

std::string Logger::to_string(Logger::TraceLevels level) {
	switch (level) {
	case Logger::TraceLevels::Trace: return "[Trace]";
	case Logger::TraceLevels::Debug: return "[Debug]";
	case Logger::TraceLevels::Info: return "[Info]";
	case Logger::TraceLevels::Warning: return "[Warning]";
	case Logger::TraceLevels::Error: return "[Error]";
	case Logger::TraceLevels::Fatal: return "[Fatal]";
	default: return "Unknown";
	}
}

std::string to_string(const char* message) {
	return std::string(message);
}

std::string to_string(char* message) {
	return std::string(message);
}

std::string Logger::getCurrentTime() {
	auto now = std::chrono::system_clock::now();
	std::time_t now_time = std::chrono::system_clock::to_time_t(now);

	std::stringstream ss;
	ss << std::put_time(std::localtime(&now_time), "%H:%M:%S");
	return ss.str();
}
