#pragma once

#include <list>
#include <string>

#include "WlanInterface.h"
#include "WlanInterfaceCapability.h"

class WifiToolInterface
{
public:
	virtual std::list<WlanInterface> EnumerateWLANInterfaces() const = 0;
	virtual WlanInterfaceCapability GetInterfaceCapability(const WlanInterface &device) const = 0;
};

