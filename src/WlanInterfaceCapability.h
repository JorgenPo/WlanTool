#pragma once

#include <Windows.h>
#include <wlanapi.h>
#include <array>
#include <list>
#include <map>

enum class WlanInterfaceType {
	EMULATED = 0,
	NATIVE,
	INVALID
};

enum WlanInterfacePhyType {
	UNKNOWN = 0,
	ANY = 0,
	FHSS = 1,
	DSSS = 2,
	IRBASEBAND = 3,
	OFDM = 4,
	HRDSSS = 5,
	ERP = 6,
	HT = 7,
	VHT = 8,
	IHV_START = 0x80000000,
	IHV_END = 0xffffffff
};

class WlanInterfaceCapability
{
	static std::map<WlanInterfaceType, std::wstring> typeToStringMap;
	static std::map<WlanInterfacePhyType, std::wstring> phyTypeToStringMap;

public:
	WlanInterfaceCapability(PWLAN_INTERFACE_CAPABILITY capability);

	WlanInterfaceType GetType() const { return this->type; }
	std::wstring GetTypeString() const;
	bool IsDotDSupported() const { return this->dotDSupported; }
	DWORD GetMaxSSIDListSize() const { return this->maxSSIDListSize; }
	DWORD GetMaxBSSIDListSize() const { return this->maxBSSIDListSize; }
	DWORD GetNumberOfSupportedPhys() const { return this->numberOfPhysSupported; }
	std::list<WlanInterfacePhyType> GetListOfSupportedPhys() const;
	std::list<std::wstring> GetListOfSupportedPhyStrings() const;

private:

	WlanInterfaceType type;
	bool dotDSupported;
	DWORD maxSSIDListSize;
	DWORD maxBSSIDListSize;
	DWORD numberOfPhysSupported;
	std::array<WlanInterfacePhyType, WLAN_MAX_PHY_INDEX> supportedPhys;
};

