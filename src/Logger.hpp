#pragma once

#include <iostream>
#include <cstdlib>

namespace Logger {

	enum class TraceLevels {
		Trace,
		Debug,
		Info,
		Warning,
		Error,
		Fatal
	};

	class TraceMessage {
	public:

		TraceMessage();
		TraceMessage(TraceLevels level, char* message);

		char* getMessage() {
			return this->message;
		}

		TraceLevels getLevel() {
			return this->level;
		}

		const char* getTime() {
			return this->time.c_str();
		}

	private:
		std::string time;
		char* message;
		TraceLevels level;
	};

	void flushTraces();
	void log(TraceLevels level, char* content);
	void log(TraceLevels level, const char* content);
	void log(TraceMessage message);

	void flushAtExit();

	void initializeLogger();

	std::string to_string(TraceMessage message);
	std::string to_string(TraceLevels level);

	std::string getCurrentTime();
}