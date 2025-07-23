// log.cpp
#include "log.h"
#include <iostream>

void Log::log(Level level, const char* message)
{
	switch (level) {
		case Level::None:
			break;
		case Level::Debug: // this one is quite hacky
#ifdef IN_DEBUG
			std::cout << "[DEBUG] " << message << std::endl;
#endif
			break;
		case Level::Info:
			std::cout << "[INFO] " << message << std::endl;
			break;
		case Level::Warning:
			std::cout << "[WARNING] " << message << std::endl;
			break;
		case Level::Error:
			std::cerr << "[ERROR] " << message << std::endl;
			break;
		case Level::Critical:
			std::cerr << "[CRITICAL] " << message << std::endl;
			exit(-1); // exit the program on critical errors
			break;
		default:
			break;
	}
}
