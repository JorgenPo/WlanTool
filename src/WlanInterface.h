#pragma once

#include <Windows.h>
#include <wlanapi.h>

#include <string>
#include <map>

enum class WlanInterfaceState {
	NOT_READY = 0,
	CONNECTED = 1,
	AD_HOC_NETWORK_FORMED = 2,
	DISCONNECTING = 3,
	DISCONNECTED = 4,
	ASSOTIATING = 5,
	DISCOVERING = 6,
	AUTHENTICATING = 7,
	NUM_STATES
};

class WlanInterface
{
	static std::map<WlanInterfaceState, std::wstring> stateMap;

public:
	WlanInterface(const WLAN_INTERFACE_INFO &info);

	GUID GetGUID() const { return this->guid; }
	std::wstring GetGUIDString() const { return this->guidString; }
	std::wstring GetDescription() const { return this->description; }
	WlanInterfaceState GetState() const { return this->state; }
	std::wstring GetStateString() const;

private:
	GUID guid;
	std::wstring description;
	std::wstring guidString;
	WlanInterfaceState state;
};

