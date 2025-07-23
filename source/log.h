// log.h
#ifndef LOG_H
#define LOG_H

class Log {
public:
	enum class Level {
		None,
		Debug,
		Info,
		Warning,
		Error,
		Critical,
		Last
	};

	static void log(Level level, const char* message);
};

#endif // LOG_H