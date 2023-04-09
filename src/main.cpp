#include <iostream>

#include "Logger.hpp"

int main(void) {
	Logger::initializeLogger();
	Logger::log(Logger::TraceLevels::Error, "ENFIN??");

	/*
	*  Next ideas :
	*  - Change char* to string or anything with better perfs because atm it sucks
	*  - Be able to change the default output (change the std::cout to an another stream, gotta looks how imgui handle the console demo for example)
	*  - Add the possibilities to write to a file
	*  - Write the docs
	*/



	return 0;
}