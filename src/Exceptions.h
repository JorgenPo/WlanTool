#pragma once

#include <minwindef.h> // For DWORD
#include <exception>
#include <string>
#include <sstream>

class ExceptionInterface {
public:
	virtual std::string GetMessage() = 0;
};

class WlanException : public ExceptionInterface {
public:
	WlanException(DWORD errorCode)
	{
		this->errorCode = errorCode;
	}

	// Унаследовано через ExceptionInterface
	virtual std::string GetMessage() override
	{
		std::ostringstream stream;
		stream << "Internal WLAN API exception. Error code = "
			<< this->errorCode;
		return stream.str();
	}

	DWORD GetErrorCode()
	{
		return this->errorCode;
	}

private:
	DWORD errorCode;
};