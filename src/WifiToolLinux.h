#pragma once

#include "WifiToolInterface.h"

class WifiToolLinux : public WifiToolInterface
{
public:
	WifiToolLinux();
	~WifiToolLinux();

	// Унаследовано через WifiToolInterface
	virtual std::list<WlanInterface> EnumerateWLANInterfaces() const override;
	/*virtual WlanInterfaceCapability GetInterfaceCapability(const WlanInterface & device) const override;*/
	virtual std::list<WlanNetwork> GetAvailableNetworksList() const override;
};

