#pragma once
#include "../../ext/ImGui 1.90/imgui.h"
#include "../../ext/ImGui 1.90/imgui_impl_win32.h"
#include "../../ext/ImGui 1.90/imgui_impl_dx11.h"
#include "../Utils/Log/log.h"
#include <dwmapi.h>
#include <thread>
#include <d3d11.h>
#include <string>
#pragma comment(lib, "d3d11.lib")

enum OverlayMode : int
{
	WINDOW_TITLE,
	WINDOW_CLASS,
	PROCESS
};

class Overlay {
	// hijack overlay dx11

private:
	// our title and class name of our overlay
	char Title[32] = "The Overlay";
	char Class[32] = "WND_CLS";

	HWND m_hwnd;
	HWND Hwnd;
	WNDCLASSEXA wc{};

	IDXGISwapChain* swap_chain;
	ID3D11Device* d3d_device;
	ID3D11DeviceContext* device_context;
	ID3D11RenderTargetView* render_target_view;

	// void HijackOverlay();
	bool CreateOverlay();
	bool ApplyWindowStyles();
	bool InitDevice();
	void CleanupDeviceD3D();

	void RenderManager();
	void CleanupRenderTarget();
	void init_render_target();
	void LoadStyle();
public:
	bool InitOverlay(const std::wstring targetName, int overlayMode);
	void OverlayLoop();
	void DestroyOverlay();
};