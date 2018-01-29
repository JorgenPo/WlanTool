#pragma once

#include <string>
#include <list>
#include <map>

#include "WlanInterfaceCapability.h"

enum class WlanBssType {
	INFRASTRUCTURE,
	INDEPENDENT,
	ANY
};

enum WlanAuthAlgorythm {
	OPEN_SYSTEM = 1,
	SHARED_KEY = 2,
	WPA = 3,
	WPA_PSK = 4,
	WPA_NONE = 5,
	RSNA = 6,
	RSNA_PSK = 7,
};

enum WlanCipherAlgorythm {
	NONE = 0x00,
	WEP40 = 0x01,
	TKIP = 0x02,
	CCMP = 0x04,
	WEP104 = 0x05,
	WPA_USE_GROUP = 0x100,
	RSN_USE_GROUP = 0x100,
	WEP = 0x101,
};

class WlanNetwork
{
	static const std::map<WlanBssType, std::wstring> bssTypeMap;
	static const std::map<WlanAuthAlgorythm, std::wstring> authAlgorythmMap;
	static const std::map<WlanCipherAlgorythm, std::wstring> cipherAlgorythmMap;

public:
	WlanNetwork(const WLAN_AVAILABLE_NETWORK &network);
	~WlanNetwork();

	std::wstring GetProfileName() const { return profileName; }
	std::wstring GetSsid() const { return ssid; }
	std::wstring GetBssTypeString() const;
	std::wstring GetAuthAlgorythmString() const;
	std::wstring GetCipherAlgorythmString() const;
	WlanBssType GetBssType() const { return bssType; }
	int GetNumberOfBssids() const { return numberOfBssids; }
	bool IsConnectable() const { return isNetworkConnectable; }
	std::wstring GetNotConnectableReason() const { return notConnectableReason; }
	int GetNumberOfPhyTypes() const { return numberOfPhyTypes; }
	const std::list<WlanInterfacePhyType>& GetPhyTypesList() const { return phyTypesList; }
	bool HasMorePhyTypes() const { return isMorePhyTypes; }
	int GetSignalQuality() const { return signalQuality; }
	bool IsSecurityEnabled() const { return isSecurityEnabled; }
	WlanAuthAlgorythm GetAuthAlgorythm() const { return authAlgorythm; }
	WlanCipherAlgorythm GetCipherAlgorythm() const { return cipherAlgorythm; }
	bool IsConnected() const { return isConnected; }
	bool HasProfile() const { return hasProfile; }

private:
	std::wstring profileName;
	std::wstring ssid;
	WlanBssType bssType;
	int numberOfBssids;
	bool isNetworkConnectable;
	std::wstring notConnectableReason;
	int numberOfPhyTypes;
	std::list<WlanInterfacePhyType> phyTypesList;
	bool isMorePhyTypes;
	int signalQuality;
	bool isSecurityEnabled;
	WlanAuthAlgorythm authAlgorythm;
	WlanCipherAlgorythm cipherAlgorythm;
	bool isConnected;
	bool hasProfile;
};

