// #include <TlHelp32.h>
#include "overlay.h"
#include "../Game/Cs2/game.h"
#include "Menu/menu.h"

ID3D11Device* g_pd3dDevice = NULL;
ID3D11DeviceContext* g_pd3dDeviceContext = NULL;



// void CleanupDeviceD3D();
void CreateRenderTarget();
//void CleanupRenderTarget();
bool CreateDeviceD3D(HWND hWnd);

bool Overlay::InitDevice() {
    DXGI_SWAP_CHAIN_DESC vSwapChainDesc;
    ZeroMemory(&vSwapChainDesc, sizeof(vSwapChainDesc));
    vSwapChainDesc.BufferCount = 2;
    vSwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    vSwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    vSwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    vSwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    vSwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    vSwapChainDesc.OutputWindow = Hwnd;
    vSwapChainDesc.SampleDesc.Count = 1;
    vSwapChainDesc.Windowed = TRUE;
    vSwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    D3D_FEATURE_LEVEL vFeatureLevel;
    D3D_FEATURE_LEVEL vFeatureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };

    if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, vFeatureLevelArray, 2, D3D11_SDK_VERSION, &vSwapChainDesc, &swap_chain, &d3d_device, &vFeatureLevel, &device_context) != S_OK) {
        return false;
    }
    init_render_target();

    ShowWindow(Hwnd, SW_SHOWNORMAL);
    UpdateWindow(Hwnd);

    return true;
}

void Overlay::init_render_target() {
	ID3D11Texture2D* vBackBuffer = nullptr;
	swap_chain->GetBuffer(0, IID_PPV_ARGS(&vBackBuffer));
	if (vBackBuffer) {
		d3d_device->CreateRenderTargetView(vBackBuffer, NULL, &render_target_view);
		Logging::debug_print("creating render target view");

    }
    else {
        /*swap_chain->CreateRenderTargetView(vBackBuffer, NULL, &render_target_view);*/
        // todo: error here if it can't get the backbuffer of the render target
        vBackBuffer->Release();
    }
}

bool Overlay::ApplyWindowStyles() {

    auto getInfo = GetWindowLongA(Hwnd, -20);
    auto changeAttributes = SetWindowLongA(Hwnd, -20, (LONG_PTR)(getInfo | 0x20));
    SetLayeredWindowAttributes(Hwnd, 0x000000, 0xFF, 0x02);
    // avoiding topmost using SetWindowPos(OurOverlayHwnd, Targethwnd, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_ASYNCWINDOWPOS)
    // for getting targetHwnd, dont use findwindow. the alternative is EnumWindows. but it still implementing soon
    // now its maybe dtctd. but for cs2 its fine to using topmost.
    SetWindowPos(Hwnd, HWND_TOPMOST, 0, 0, 0, 0, 0x0002 | 0x0001);
	if (!Hwnd) {
		Logging::error_print("cant apply window styles");
		return false;
	}
    RECT client_area{};
    GetClientRect(Hwnd, &client_area);
    RECT window_area{};
    GetWindowRect(Hwnd, &window_area);
    POINT diff{};
    ClientToScreen(Hwnd, &diff);
    const MARGINS margins{ window_area.left + (diff.x - window_area.left), window_area.top + (diff.y - window_area.top), client_area.right, client_area.bottom };
    DwmExtendFrameIntoClientArea(Hwnd, &margins);

    Menu::LoadStyle();

    ImGui_ImplWin32_Init(Hwnd);
    ImGui_ImplDX11_Init(d3d_device, device_context);

	return true;
}

void Overlay::CleanupRenderTarget() {
	if (render_target_view) { render_target_view->Release(); render_target_view = NULL; }
}
void Overlay::CleanupDeviceD3D()
{

    CleanupRenderTarget();

    if (swap_chain) { swap_chain->Release(); swap_chain = NULL; }
    if (device_context) { device_context->Release(); device_context = NULL; }
    if (d3d_device) { d3d_device->Release(); d3d_device = NULL; }
}

void Overlay::DestroyOverlay() {
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    CleanupDeviceD3D();
    DestroyWindow(Hwnd);
    UnregisterClassA(wc.lpszClassName, wc.hInstance);
}




// what where we are render so if we render in cs2 render in cs2
void Overlay::RenderManager() {
    /*HWND CheckHwnd = FindWindowA(targetName, nullptr);
    if (!CheckHwnd) {
        GlobalsConfig.Run = false;
        Logging::error_print("game %s not found", targetName);
        return;
    }*/
    DWORD Flag = NULL;
    GetWindowDisplayAffinity(Hwnd, &Flag);
    if (GlobalsConfig.StreamProof && Flag == WDA_NONE) {
        SetWindowDisplayAffinity(Hwnd, WDA_EXCLUDEFROMCAPTURE);
    }
    else if (!GlobalsConfig.StreamProof && Flag == WDA_EXCLUDEFROMCAPTURE) {
        SetWindowDisplayAffinity(Hwnd, WDA_NONE);
    }
    HWND ForegroundWindow = GetForegroundWindow();
    LONG TmpLong = GetWindowLong(Hwnd, GWL_EXSTYLE);

  

    static bool menu_key = false;
    if (IsKeyDown(GlobalsConfig.MenuKey) && !menu_key)
    {
        GlobalsConfig.ShowMenu = !GlobalsConfig.ShowMenu;

        if (GlobalsConfig.ShowMenu && ForegroundWindow != Hwnd) {
            SetForegroundWindow(Hwnd);
        }
     /*   else if (!GlobalsConfig.ShowMenu && ForegroundWindow != CheckHwnd)
            SetForegroundWindow(CheckHwnd);*/

        menu_key = true;
    }
    else if (!IsKeyDown(GlobalsConfig.MenuKey) && menu_key)
    {
        menu_key = false;
    }
    
}
void Overlay::OverlayLoop() {
    if (!Hwnd) {
        Logging::error_print("cant start overlay loop");
        return;
    }
    while (GlobalsConfig.Run) {
        if (!GlobalsConfig.Run) {
            break;
        }
            
        MSG msg;
        const float clear_color_with_alpha[4] = { 0.f, 0.f, 0.f, 0.f };

        if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }
    
        RenderManager();
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        float window_width = GetSystemMetrics(SM_CXSCREEN);
        float window_height = GetSystemMetrics(SM_CYSCREEN);
        GlobalsConfig.GameRect.right = window_width;
		GlobalsConfig.GameRect.bottom = window_height;
        // our render cheat
        Cs2::RenderEntity();

        ImGui::Render();
        device_context->OMSetRenderTargets(1, &render_target_view, NULL);
        device_context->ClearRenderTargetView(render_target_view, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        swap_chain->Present(1, 0);
    }
}

bool Overlay::InitOverlay(const std::wstring targetName, int overlayMode) {
    // example usage initOverlay for nvidia: FindWindowA("CEF-OSC-WIDGET", "NVIDIA GeForce Overlay");
    // FindWindowA("CEF-OSC-WIDGET", "NVIDIA GeForce Overlay");
    // ik it maybe dtc. i'll find the alternative

    if (overlayMode == WINDOW_TITLE || overlayMode == WINDOW_CLASS) {
        Hwnd = FindWindowW(L"CEF-OSC-WIDGET", targetName.c_str());

        if (!Hwnd) {
            Logging::error_print("cant init overlay, target %ls app not found", targetName.c_str());
            return false;
        }

    }
    else if (overlayMode == PROCESS) {
        // overlaymode proccess is most detected also not yet implemented GetTargetWindow
       /* m_hwnd = GetTargetWindow(targetName);

        if (!m_hwnd) {
            Logging::error_print("cant init overlay, target app not found");
            return false;
        }*/
    }
    else {
        Logging::error_print("WRONG Mode of initing overlay");
        return false;
    }

    // coming-soon without top-most using this implementation, reff : https://github.com/BrynhildrWare/NvidiaHijackSharp
    //targetHwnd = FindWindowAlt(L"SDL_app", L"Counter-Strike 2");
   /* public static IntPtr FindWindowAlt(string ClassName, string WindowName)
    {
        IEnumerable<IntPtr> Windows = FindWindows(delegate(IntPtr wnd, IntPtr param)
        {
            return GetWindowText(wnd).Contains(WindowName) && GetClassName(wnd).Contains(ClassName);
        });

        return Windows.DefaultIfEmpty(IntPtr.Zero).First();
    }*/

    if (!InitDevice()) {
		Logging::error_print("cant init device");
        return false;
    }
	if (!ApplyWindowStyles()) {
		Logging::error_print("cant apply window styles");
		return false;
	}
    
}