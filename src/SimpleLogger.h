#pragma once


#include "LoggerInterface.h"

#include <map>
#include <string>

class SimpleLogger :
	public LoggerInterface
{
public:
	SimpleLogger();

	// Унаследовано через LoggerInterface
	virtual void log(LogLevel level, std::string message, va_list args) const override;
	virtual void Error(std::string message, ...) const override;
	virtual void Debug(std::string message, ...) const override;
	virtual void Info(std::string message, ...) const override;
	virtual void SetLogLevel(LogLevel level) override;

private:
	LogLevel logLevel;
	std::map<LogLevel, std::string> logLevelMap;
};

