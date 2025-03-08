#pragma once
#include "../../ext/ImGui 1.90/imgui.h"
#include "../../ext/ImGui 1.90/imgui_impl_win32.h"
#include "../../ext/ImGui 1.90/imgui_impl_dx11.h"
#include <dwmapi.h>
#include <thread>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

class Overlay {
private:
	HWND m_hwnd;

	bool CreateOverlay();
public:
};