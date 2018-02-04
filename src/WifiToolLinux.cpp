#include "WifiToolLinux.h"



WifiToolLinux::WifiToolLinux()
{
}


WifiToolLinux::~WifiToolLinux()
{
}

std::list<WlanInterface> WifiToolLinux::EnumerateWLANInterfaces() const
{
	return std::list<WlanInterface>();
}

//WlanInterfaceCapability WifiToolLinux::GetInterfaceCapability(const WlanInterface & device) const
//{
//	return WlanInterfaceCapability();
//}

std::list<WlanNetwork> WifiToolLinux::GetAvailableNetworksList() const
{
	return std::list<WlanNetwork>();
}
