#include "SimpleLogger.h"

#include <ctime>
#include <iostream>
#include <string>

using namespace std;

SimpleLogger::SimpleLogger()
	: logLevel(LogLevel::ERRORS)
{
	this->logLevelMap[LogLevel::ERRORS] = "Error";
	this->logLevelMap[LogLevel::INFO] = "Info";
	this->logLevelMap[LogLevel::DEBUG] = "Debug";
}

void SimpleLogger::log(LogLevel level, string message, va_list args) const
{
	if (level > this->logLevel) {
		return;
	}

	time_t t = time(0);
	struct tm* now = localtime(&t);

	cout << (now->tm_year + 1900) << '-'
		<< (now->tm_mon + 1) << '-'
		<< now->tm_mday
		<< ' ' << now->tm_hour
		<< ':' << now->tm_min
		<< ':' << now->tm_sec
		<< ' ';

	cout << '[' << this->logLevelMap.at(level) << "] ";

	size_t length = 5000;

	// TODO: count strings in args too
	char* buffer = new char[length];
	vsprintf_s(buffer, length, message.c_str(), args);
	message = buffer;

	cout << message << '\n';

	delete buffer;
}

void SimpleLogger::Error(string message, ...) const
{
	va_list args;
	va_start(args, message);
	this->log(LogLevel::ERRORS, message, args);
	va_end(args);
}

void SimpleLogger::Debug(string message, ...) const
{
	va_list args;
	va_start(args, message);
	this->log(LogLevel::DEBUG, message, args);
	va_end(args);
}

void SimpleLogger::Info(string message, ...) const
{
	va_list args;
	va_start(args, message);
	this->log(LogLevel::INFO, message, args);
	va_end(args);
}

void SimpleLogger::SetLogLevel(LogLevel level)
{
	this->logLevel = level;
}
