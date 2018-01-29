#include "WifiToolWindows.h"

#include "SimpleLogger.h"
#include "Exceptions.h"

WifiToolWindows::WifiToolWindows()
{
	logger = std::make_unique<SimpleLogger>();
	logger->SetLogLevel(LogLevel::ERRORS);

	DWORD dwResult = 0;
	DWORD dwVersionUsed = 0;

	dwResult = WlanOpenHandle(MaxClientVersion, nullptr, &dwVersionUsed, &this->clientHandle);
	if (dwResult != ERROR_SUCCESS) {
		this->logger->Error("WlanOpenHandle failed with error %u", dwResult);
		exit(1);
	}

	this->logger->Info("WlanOpenHandle success. Using WLAN API version %u", dwVersionUsed);
}


WifiToolWindows::~WifiToolWindows()
{
	WlanCloseHandle(this->clientHandle, nullptr);
}

std::list<WlanInterface> WifiToolWindows::EnumerateWLANInterfaces() const
{
	std::list<WlanInterface> result;

	PWLAN_INTERFACE_INFO_LIST pInfoList = nullptr;
	PWLAN_INTERFACE_INFO pInfo = nullptr;

	DWORD dwResult = 0;

	dwResult = WlanEnumInterfaces(this->clientHandle, nullptr, &pInfoList);
	if (dwResult != ERROR_SUCCESS) {
		this->logger->Error("WlanEnumInterfaces failed with error %u", dwResult);
		throw WlanException(dwResult);
	}

	this->logger->Debug("WlanEnumInterfaces found %lu interfaces", pInfoList->dwNumberOfItems);

	for (uint32_t i = 0; i < pInfoList->dwNumberOfItems; ++i) {
		result.push_back(WlanInterface(pInfoList->InterfaceInfo[i]));
	}

	WlanFreeMemory(pInfoList);

	return result;
}

WlanInterfaceCapability WifiToolWindows::GetInterfaceCapability(const WlanInterface &device) const
{
	DWORD result = 0;
	PWLAN_INTERFACE_CAPABILITY capability;

	result = WlanGetInterfaceCapability(this->clientHandle, &device.GetGUID(), nullptr, &capability);
	if (result != ERROR_SUCCESS) {
		this->logger->Error("WlanGetInterfaceCapability failed with error %u", result);
		throw WlanException(result);
	}

	this->logger->Info("Interface support %S phy types!", 
		device.GetGUIDString().c_str(), capability->dwNumberOfSupportedPhys);

	return WlanInterfaceCapability(capability);
}

std::list<WlanNetwork> WifiToolWindows::GetAvailableNetworksList() const
{
	std::list<WlanNetwork> resultList;

	auto list = this->EnumerateWLANInterfaces();

	// First interface
	WlanInterface& defaultInterface = list.front();

	this->logger->Info("GetAvailableNetworkList Using default interface %S", 
		defaultInterface.GetGUIDString());

	PWLAN_AVAILABLE_NETWORK_LIST networkList;

	DWORD result = WlanGetAvailableNetworkList(clientHandle, 
		&defaultInterface.GetGUID(), 0, nullptr, &networkList);

	if (result != ERROR_SUCCESS) {
		this->logger->Error("WlanGetInterfaceCapability failed with error %u", result);
		throw WlanException(result);
	}

	for (size_t i = 0; i < networkList->dwNumberOfItems; ++i) {
		resultList.push_back(WlanNetwork(networkList->Network[i]));
	}

	WlanFreeMemory(networkList);

	return resultList;
}
