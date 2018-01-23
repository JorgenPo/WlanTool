#include "WlanInterface.h"

std::map<WlanInterfaceState, std::wstring> WlanInterface::stateMap = {
	{ WlanInterfaceState::AD_HOC_NETWORK_FORMED,	L"The interface is the first node in an ad hoc network. No peer has connected." },
	{ WlanInterfaceState::ASSOTIATING,				L"The interface is attempting to associate with a network." },
	{ WlanInterfaceState::AUTHENTICATING,			L"The interface is in the process of authenticating." },
	{ WlanInterfaceState::CONNECTED,				L"The interface is connected to a network." },
	{ WlanInterfaceState::DISCONNECTED,				L"The interface is not connected to any network." },
	{ WlanInterfaceState::DISCONNECTING,			L"The interface is disconnecting from the current network." },
	{ WlanInterfaceState::DISCOVERING,				L"Auto configuration is discovering the settings for the network." },
	{ WlanInterfaceState::NOT_READY,				L"The interface is not ready to operate." },
};

WlanInterface::WlanInterface(const WLAN_INTERFACE_INFO &info)
{
	this->guid = info.InterfaceGuid;
	this->description = info.strInterfaceDescription;
	this->state = static_cast<WlanInterfaceState>(info.isState);

	WCHAR guidString[40] = { 0 };

	int result = StringFromGUID2(this->guid, (LPOLESTR) &guidString, 39);

	if (result == 0) {
		this->guidString = L"<UNKNOWN>";
	}
	else {
		this->guidString = guidString;
	}
}

std::wstring WlanInterface::GetStateString() const
{
	return WlanInterface::stateMap[this->state];
}

