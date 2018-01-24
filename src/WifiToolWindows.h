#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include <Windows.h>
#include <wlanapi.h>
#include <memory>

#include "WifiToolInterface.h"
#include "LoggerInterface.h"
#include "WlanInterface.h"
#include "WlanInterfaceCapability.h"

#pragma comment(lib, "wlanapi.lib")
#pragma comment(lib, "ole32.lib")

class WifiToolWindows :
	public WifiToolInterface
{
	static constexpr DWORD MaxClientVersion = 2;

public:
	WifiToolWindows();
	~WifiToolWindows();

	// Унаследовано через WifiCrackerInterface
	virtual std::list<WlanInterface> EnumerateWLANInterfaces() const override;
	virtual WlanInterfaceCapability GetInterfaceCapability(const WlanInterface &device) const override;

private:
	HANDLE clientHandle;
	std::unique_ptr<LoggerInterface> logger;
	
};

