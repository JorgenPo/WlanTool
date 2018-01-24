#include "WifiToolWindows.h"

#include <memory>
#include <list>
#include <iostream>

using namespace std;

int main()
{
	auto wifiCracker = make_unique<WifiToolWindows>();

	list<WlanInterface> interfaces = wifiCracker->EnumerateWLANInterfaces();

	wcout << "Enumerating wlan interfaces:" << '\n';
	for (auto& elem : interfaces) {
		WlanInterfaceCapability capability = wifiCracker->GetInterfaceCapability(elem);

		wcout << '\n';
		wcout << "=======Interface " << elem.GetGUIDString() << "=======" << '\n';
		wcout << "Interface information:" << '\n';
		wcout << "  Interface guid: " << elem.GetGUIDString() << '\n';
		wcout << "  Interface name: " << elem.GetDescription() << '\n';
		wcout << "  Interface state: " << elem.GetStateString() << '\n';
		wcout << "Interface capabilities: " << '\n';
		wcout << "  Type: " << capability.GetTypeString() << '\n';
		wcout << "  Max ssid list size: " << capability.GetMaxSSIDListSize() << '\n';
		wcout << "  Max bssid list size: " << capability.GetMaxBSSIDListSize() << '\n';
		wcout << "  Support of 802.11d: " << capability.IsDotDSupported() << '\n';
		wcout << "Supported phy types(" << capability.GetNumberOfSupportedPhys() << ')' << ":\n";
		
		for (auto& phyType : capability.GetListOfSupportedPhyStrings()) {
			wcout << " -" << phyType << '\n';
		}

		wcout << "==============================================================\n";
		wcout << '\n';
	}

	return 0;
}