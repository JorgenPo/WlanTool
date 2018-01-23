#pragma once

#include <list>
#include <string>

#include "WlanInterface.h"

class WifiCrackerInterface
{
public:
	virtual std::list<WlanInterface> EnumerateWLANInterfaces() const = 0;
};

