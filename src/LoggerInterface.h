#pragma once

#include <string>
#include <stdarg.h>

enum class LogLevel
{
	ERRORS = 0,
	INFO  = 1,
	DEBUG = 2,
};

class LoggerInterface
{
public:
	virtual void log(LogLevel level, std::string message, va_list args) const = 0;
	virtual void Error(std::string message, ...) const = 0;
	virtual void Debug(std::string message, ...) const = 0;
	virtual void Info(std::string message, ...) const = 0;
	virtual void SetLogLevel(LogLevel level) = 0;
};

