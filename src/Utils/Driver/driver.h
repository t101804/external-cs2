#pragma once
#include "../header.h"

namespace codes {
    constexpr ULONG init = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x696, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
    constexpr ULONG read = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x697, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
    constexpr ULONG write = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x698, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
};



struct info_t {
	HANDLE target_pid = 0; //process id of process we want to read from / write to
	void* target_address = 0x0; //address in the target proces we want to read from / write to
	void* buffer_address = 0x0; //address in our usermode process to copy to (read mode) / read from (write mode)
	SIZE_T size = 0; //size of memory to copy between our usermode process and target process
	SIZE_T return_size = 0; //number of bytes successfully read / written
};


//struct ViewMatrix {
//	ViewMatrix() noexcept : data() {}
//	float* operator[](int index) noexcept { return data[index]; }
//	const float* operator[](int index) const noexcept { return data[index]; }
//	float data[4][4];
//};
//
//static bool worldToScreen(const Vector3 world, Vector3& screen, const ViewMatrix& vm) {
//	float w = vm[3][0] * world.x + vm[3][1] * world.y + vm[3][2] * world.z + vm[3][3];
//
//	if (w < 0.001f) {
//		return false;
//	}
//
//	const float x = world.x * vm[0][0] + world.y * vm[0][1] + world.z * vm[0][2] + vm[0][3];
//	const float y = world.x * vm[1][0] + world.y * vm[1][1] + world.z * vm[1][2] + vm[1][3];
//
//	w = 1.f / w;
//	float nx = x * w;
//	float ny = y * w;
//
//	const ImVec2 size = ImGui::GetIO().DisplaySize;
//	screen.x = (size.x * 0.5f * nx) + (nx + size.x * 0.5f);
//	screen.y = -(size.y * 0.5f * ny) + (ny + size.y * 0.5f);
//
//	return true;
//}

class driver_manager {
    
public:
	
	static HANDLE m_driver_handle; //handle to our driver
	static bool find_driver(const char* driver_name);
	static void read_virtual_memory(PVOID address, PVOID buffer, DWORD size);
	static void write_virtual_memory(PVOID address, PVOID buffer, DWORD size);
	static void attach_to_process(DWORD process_id);
	static std::wstring get_base_module(DWORD process_id);
	static DWORD get_process_id(const wchar_t* process_name);
	//static uintptr_t get_base_address();
	static std::uintptr_t get_module_base_address(DWORD process_id, const wchar_t* module_name);
};

template<typename T>
T read_mem(const std::uintptr_t address) {
	T read_data;
	driver_manager::read_virtual_memory(reinterpret_cast<PVOID>(address), &read_data, sizeof(T));
	return read_data;
}

template<typename T>
void write_mem(const std::uintptr_t address, const T& buffer) {
	driver_manager::write_virtual_memory(reinterpret_cast<PVOID>(address), (PVOID)&buffer, sizeof(T));
}

