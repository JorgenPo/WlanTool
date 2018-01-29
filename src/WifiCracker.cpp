#include "WifiCracker.h"
#include "WifiToolWindows.h"

#include <iostream>

WifiCracker::WifiCracker()
	: subcommand("undefined")
{
//#ifdef WINDOWS
	this->wlanTool = std::make_unique<WifiToolWindows>();
//#else
	//wlanTool = std::make_unique<WifiToolLinux>();
//#endif
	this->cli = std::make_unique<CLI::App>("Wifi cracking crossplatform tool");

	this->listNetworksCli = this->cli->add_subcommand("listNetworks", "List available wifi networks");
	this->listInterfacesCli = this->cli->add_subcommand("listInterfaces", "List available wlan interfaces");
	this->infoCli = this->cli->add_subcommand("info", "Prints info about network or interface");

	// Require one and only subcommand
	this->cli->require_subcommand(1, 1);
}


WifiCracker::~WifiCracker()
{
	// cli pointers deletes automaticly when parent cli goes out of scope
}

int WifiCracker::Run(int argc, char ** argv)
{
	try 
	{
		this->cli->parse(argc, argv);
	}
	catch (const CLI::ParseError &e) {
		return this->cli->exit(e);
	}

	if (this->listInterfacesCli->parsed()) {
		this->ListInterfaces();
	}
	else if (this->listNetworksCli->parsed()) {
		this->ListWifiNetworks();
	}

	return 0;
}

void WifiCracker::ListInterfaces()
{
	using namespace std;

	list<WlanInterface> interfaces = this->wlanTool->EnumerateWLANInterfaces();

	wcout << "Enumerating wlan interfaces:" << '\n';
	for (auto& elem : interfaces) {
		WlanInterfaceCapability capability = this->wlanTool->GetInterfaceCapability(elem);

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
}

void WifiCracker::ListWifiNetworks()
{
	using namespace std;

	list<WlanNetwork> networks = this->wlanTool->GetAvailableNetworksList();

	wcout << "Available wlan networks:" << "\n\n";
	for (auto& network : networks) {
		wcout << "Network \"" << network.GetSsid() << "\" ";
		
		// Connecting
		if (network.IsConnected()) {
			wcout << "(CONNECTED) ";
		}
		else if (!network.IsConnectable()) {
			wcout << "(NOT CONNACTABLE) ";
		}

		// Signal quality
		wcout << "|";
		for (int i = 0; i < 10; ++i) {
			if (network.GetSignalQuality() >= (i * 10)) {
				wcout << "#";
			}
			else {
				wcout << ".";
			}
		}
		wcout << "|\n";

		wcout << " SSID: " << network.GetSsid() << '\n';
		wcout << " Profile Name: " << network.GetProfileName() << '\n';

		if (network.IsSecurityEnabled()) {
			wcout << " Security algorythm: " << network.GetAuthAlgorythmString() << '\n';
			wcout << " Security cipher: " << network.GetCipherAlgorythmString() << '\n';
		}

		if (!network.IsConnectable()) {
			wcout << " Not connectable reason: " << network.GetNotConnectableReason() << '\n';
		}

		wcout << '\n';
	}
}
