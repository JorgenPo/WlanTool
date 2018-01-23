#include "WifiCrackerWindows.h"

#include <memory>
#include <list>
#include <iostream>

using namespace std;

int main()
{
	auto wifiCracker = make_unique<WifiCrackerWindows>();

	list<WlanInterface> interfaces = wifiCracker->EnumerateWLANInterfaces();

	wcout << "Enumerating wlan interfaces:" << '\n';
	for (auto& elem : interfaces) {
		wcout << '\n';
		wcout << "=======Interface " << elem.GetGUIDString() << "=======" << '\n';
		wcout << " Interface guid: " << elem.GetGUIDString() << '\n';
		wcout << " Interface name: " << elem.GetDescription() << '\n';
		wcout << " Interface state: " << elem.GetStateString() << '\n';
		wcout << '\n';
	}

	return 0;
}