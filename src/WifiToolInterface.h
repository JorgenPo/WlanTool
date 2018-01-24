#pragma once

#include <list>
#include <string>

#include "WlanInterface.h"

class WifiToolInterface
{
public:
	virtual std::list<WlanInterface> EnumerateWLANInterfaces() const = 0;
	virtual void GetInterfaceCapability() const = 0;
};

