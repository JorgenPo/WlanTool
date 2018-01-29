#pragma once

#include "lib/CLI11.hpp"

#include "WifiToolWindows.h"

#include <memory>
#include <list>

class WifiCracker
{
public:
	WifiCracker();
	~WifiCracker();

	int Run(int argc, char **argv);

private:
	void ListInterfaces();
	void ListWifiNetworks();

private:
	std::unique_ptr<CLI::App> cli;		// Main CLI App
	CLI::App* listNetworksCli;			// For listNetworks subcommand
	CLI::App* listInterfacesCli;		// For listInterfaces subcommand
	CLI::App* infoCli;					// For info subcommand

	std::unique_ptr<WifiToolInterface> wlanTool;
	std::string subcommand;
};

