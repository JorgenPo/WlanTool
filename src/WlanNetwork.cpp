#include "WlanNetwork.h"

const std::map<WlanBssType, std::wstring>  WlanNetwork::bssTypeMap = {
	{ WlanBssType::INFRASTRUCTURE, L"Infrastructure network" },
	{ WlanBssType::INDEPENDENT, L"Independent BSS (IBSS) network" },
	{ WlanBssType::ANY, L"Either infrastructure or IBSS network" }
};


const std::map<WlanAuthAlgorythm, std::wstring> WlanNetwork::authAlgorythmMap = {
	{ WlanAuthAlgorythm::OPEN_SYSTEM, L"Open System authentication algorithm" },
	{ WlanAuthAlgorythm::SHARED_KEY, L"Shared Key authentication algorithm" },
	{ WlanAuthAlgorythm::WPA, L"Specifies a Wi-Fi Protected Access (WPA) algorithm" },
	{ WlanAuthAlgorythm::WPA_PSK, L"Specifies a WPA algorithm that uses preshared keys (PSK)" },
	{ WlanAuthAlgorythm::WPA_NONE, L"WPA None" },
	{ WlanAuthAlgorythm::RSNA, L"Specifies an Robust Security Network Association (RSNA) algorithm" },
	{ WlanAuthAlgorythm::RSNA_PSK, L"Specifies an RSNA algorithm that uses PSK" },
};

const std::map<WlanCipherAlgorythm, std::wstring> WlanNetwork::cipherAlgorythmMap = {
	{ WlanCipherAlgorythm::NONE, L"No cipher algorithm is enabled or supported" },
	{ WlanCipherAlgorythm::WEP40, L"Wired Equivalent Privacy (WEP) algorithm" },
	{ WlanCipherAlgorythm::TKIP, L"Temporal Key Integrity Protocol (TKIP) algorithm" },
	{ WlanCipherAlgorythm::CCMP, L"AES-CCMP algorithm" },
	{ WlanCipherAlgorythm::WEP104, L"WEP cipher algorithm" },
	{ WlanCipherAlgorythm::WPA_USE_GROUP, L"Wi-Fi Protected Access (WPA) Use Group Key cipher suite" },
	{ WlanCipherAlgorythm::RSN_USE_GROUP, L"Robust Security Network (RSN) Use Group Key cipher suite" },
	{ WlanCipherAlgorythm::WEP, L" WEP cipher algorithm with a cipher key of any length" },
};

WlanNetwork::WlanNetwork(const WLAN_AVAILABLE_NETWORK &network)
{
	profileName = network.strProfileName;

	std::string temp = reinterpret_cast<const char*>(network.dot11Ssid.ucSSID);
	ssid = std::wstring(temp.begin(), temp.end());

	bssType = static_cast<WlanBssType>(network.dot11BssType);
	numberOfBssids = static_cast<int>(network.uNumberOfBssids);
	isNetworkConnectable = network.bNetworkConnectable;

	WCHAR buffer[2048];
	DWORD result = WlanReasonCodeToString(network.wlanNotConnectableReason, 2048, buffer, nullptr);

	if (result != ERROR_SUCCESS) {
		notConnectableReason = L"Reason unknown";
	}

	notConnectableReason = buffer;

	numberOfPhyTypes = static_cast<int>(network.uNumberOfPhyTypes);

	for (size_t i = 0; i < network.uNumberOfPhyTypes; ++i) {
		phyTypesList.push_back(static_cast<WlanInterfacePhyType>(network.dot11PhyTypes[i]));
	}

	signalQuality = static_cast<int>(network.wlanSignalQuality);
	isSecurityEnabled = network.bSecurityEnabled;
	authAlgorythm = static_cast<WlanAuthAlgorythm>(network.dot11DefaultAuthAlgorithm);
	cipherAlgorythm = static_cast<WlanCipherAlgorythm>(network.dot11DefaultCipherAlgorithm);

	isConnected = network.dwFlags & WLAN_AVAILABLE_NETWORK_CONNECTED;
	hasProfile = network.dwFlags & WLAN_AVAILABLE_NETWORK_HAS_PROFILE;
}

WlanNetwork::~WlanNetwork()
{
}

std::wstring WlanNetwork::GetBssTypeString() const
{
	return WlanNetwork::bssTypeMap.at(this->bssType);
}

std::wstring WlanNetwork::GetAuthAlgorythmString() const
{
	return WlanNetwork::authAlgorythmMap.at(this->authAlgorythm);
}

std::wstring WlanNetwork::GetCipherAlgorythmString() const
{
	return WlanNetwork::cipherAlgorythmMap.at(this->cipherAlgorythm);
}
