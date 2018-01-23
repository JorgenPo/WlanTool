#pragma once

#include "WifiCrackerInterface.h"

#ifndef UNICODE
#define UNICODE
#endif

#include <Windows.h>
#include <wlanapi.h>
#include <memory>

#include "LoggerInterface.h"
#include "WlanInterface.h"

#pragma comment(lib, "wlanapi.lib")
#pragma comment(lib, "ole32.lib")

class WifiCrackerWindows :
	public WifiCrackerInterface
{
	static constexpr DWORD MaxClientVersion = 2;

public:
	WifiCrackerWindows();
	~WifiCrackerWindows();

	// Унаследовано через WifiCrackerInterface
	virtual std::list<WlanInterface> EnumerateWLANInterfaces() const override;

private:
	HANDLE clientHandle;
	std::unique_ptr<LoggerInterface> logger;
};

