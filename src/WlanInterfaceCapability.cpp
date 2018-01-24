#include "WlanInterfaceCapability.h"

std::map<WlanInterfaceType, std::wstring> WlanInterfaceCapability::typeToStringMap = {
	{WlanInterfaceType::EMULATED,	L"Emulated 802.11 interface"},
	{WlanInterfaceType::NATIVE,		L"Native 802.11 interface" },
	{WlanInterfaceType::INVALID,	L"Invalid interface" }
};

std::map<WlanInterfacePhyType, std::wstring> WlanInterfaceCapability::phyTypeToStringMap = {
	{ WlanInterfacePhyType::UNKNOWN,		L"Unknown or uninitialized PHY type" },
	{ WlanInterfacePhyType::ANY,			L"Any PHY type" },
	{ WlanInterfacePhyType::FHSS,			L"Frequency-hopping spread-spectrum (FHSS) PHY" },
	{ WlanInterfacePhyType::DSSS,			L"Direct sequence spread spectrum (DSSS) PHY type" },
	{ WlanInterfacePhyType::IRBASEBAND,		L"Infrared (IR) baseband PHY type" },
	{ WlanInterfacePhyType::OFDM,			L"Orthogonal frequency division multiplexing (OFDM) PHY type" },
	{ WlanInterfacePhyType::HRDSSS,			L"High-rate DSSS (HRDSSS) PHY type" },
	{ WlanInterfacePhyType::ERP,			L"Extended rate PHY type (ERP)" },
	{ WlanInterfacePhyType::HT,				L"802.11n PHY type" },
	{ WlanInterfacePhyType::VHT,			L"802.11ac PHY type" },
	{ WlanInterfacePhyType::IHV_START,		L"Start of independent hardware vendor types" },
	{ WlanInterfacePhyType::IHV_END,		L"End of independent hardware vendor types" },
};

WlanInterfaceCapability::WlanInterfaceCapability(PWLAN_INTERFACE_CAPABILITY capability)
{
	this->dotDSupported = capability->bDot11DSupported;
	this->maxSSIDListSize = capability->dwMaxDesiredSsidListSize;
	this->maxBSSIDListSize = capability->dwMaxDesiredBssidListSize;
	this->numberOfPhysSupported = capability->dwNumberOfSupportedPhys;
	this->type = static_cast<WlanInterfaceType>(capability->interfaceType);

	
	for (uint32_t i = 0; i < this->numberOfPhysSupported; ++i) {
		this->supportedPhys[i] = static_cast<WlanInterfacePhyType>(
			capability->dot11PhyTypes[i]);
	}
}

std::wstring WlanInterfaceCapability::GetTypeString() const
{
	return WlanInterfaceCapability::typeToStringMap.at(this->type);
}

std::list<WlanInterfacePhyType> WlanInterfaceCapability::GetListOfSupportedPhys() const
{
	std::list<WlanInterfacePhyType> list(this->numberOfPhysSupported);
	std::copy_n(this->supportedPhys.begin(), this->numberOfPhysSupported, list.begin());

	return list;
}

// TODO: improve method
std::list<std::wstring> WlanInterfaceCapability::GetListOfSupportedPhyStrings() const
{
	std::list<std::wstring> strings;

	for (auto& phy : this->GetListOfSupportedPhys()) {
		strings.push_back(WlanInterfaceCapability::phyTypeToStringMap[phy]);
	}

	return strings;
}
