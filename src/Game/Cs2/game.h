#pragma once
#include "../../Utils/Log/log.h"

class Cs2 {
public:
	DWORD ProcId;
	static uintptr_t client_dll;
	static uintptr_t server_dll;
public:
	void Start();
private:
	bool DetectGame() {
	
		ProcId = driver_manager::get_process_id(L"cs2.exe");
		if (!ProcId) {
			Logging::debug_print("cant get the game cs2.exe");
			return false;
		}
		
		Logging::debug_print("pid target found : %ld", ProcId);
		return true;
	}

	bool Setup() {
		std::string driver_initial_path = "\\\\.\\";
		std::string driver_name = GlobalsConfig.DriverName;
		std::string full_driver_path = driver_initial_path + driver_name;
	
		bool driver = driver_manager::find_driver(full_driver_path.c_str());
		if (!driver) {
			Logging::debug_print("Failed to find driver");
			return false;
		}

		driver_manager::attach_to_process(ProcId);
		std::wstring baseName = driver_manager::get_base_module(ProcId);
		client_dll = driver_manager::get_module_base_address(ProcId, L"client.dll");
		server_dll = driver_manager::get_module_base_address(ProcId, L"server.dll");
		if (client_dll == 0 || server_dll == 0) {
			Logging::debug_print("cant get the base address of the library");
			return false;
		}
		Logging::debug_print("client.dll : %p, server.dll : %p", client_dll, server_dll);
		return true;
	}

};