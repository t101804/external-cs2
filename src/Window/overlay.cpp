// #include <TlHelp32.h>
#include "overlay.h"
#include "../Game/Cs2/game.h"

ID3D11Device* g_pd3dDevice = NULL;
ID3D11DeviceContext* g_pd3dDeviceContext = NULL;



// void CleanupDeviceD3D();
void CreateRenderTarget();
//void CleanupRenderTarget();
bool CreateDeviceD3D(HWND hWnd);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void Overlay::LoadStyle()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiStyle& style = ImGui::GetStyle();

    style.Alpha = 1.0f;
    style.DisabledAlpha = 1.0f;
    style.WindowPadding = ImVec2(12.0f, 12.0f);
    style.WindowRounding = 11.5f;
    style.WindowBorderSize = 0.0f;
    style.WindowMinSize = ImVec2(20.0f, 20.0f);
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style.WindowMenuButtonPosition = ImGuiDir_Right;
    style.ChildRounding = 0.0f;
    style.ChildBorderSize = 1.0f;
    style.PopupRounding = 0.0f;
    style.PopupBorderSize = 1.0f;
    style.FramePadding = ImVec2(20.0f, 3.400000095367432f);
    style.FrameRounding = 11.89999961853027f;
    style.FrameBorderSize = 0.0f;
    style.ItemSpacing = ImVec2(4.300000190734863f, 5.5f);
    style.ItemInnerSpacing = ImVec2(7.099999904632568f, 1.799999952316284f);
    style.CellPadding = ImVec2(12.10000038146973f, 9.199999809265137f);
    style.IndentSpacing = 0.0f;
    style.ColumnsMinSpacing = 4.900000095367432f;
    style.ScrollbarSize = 11.60000038146973f;
    style.ScrollbarRounding = 15.89999961853027f;
    style.GrabMinSize = 3.700000047683716f;
    style.GrabRounding = 20.0f;
    style.TabRounding = 0.0f;
    style.TabBorderSize = 0.0f;
    style.TabMinWidthForCloseButton = 0.0f;
    style.ColorButtonPosition = ImGuiDir_Right;
    style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
    style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

    style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.2745098173618317f, 0.3176470696926117f, 0.4509803950786591f, 1.0f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.09250493347644806f, 0.100297249853611f, 0.1158798336982727f, 1.0f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.1120669096708298f, 0.1262156516313553f, 0.1545064449310303f, 1.0f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.09803921729326248f, 0.105882354080677f, 0.1215686276555061f, 1.0f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.9725490212440491f, 1.0f, 0.4980392158031464f, 1.0f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.971993625164032f, 1.0f, 0.4980392456054688f, 1.0f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(1.0f, 0.7953379154205322f, 0.4980392456054688f, 1.0f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.1821731775999069f, 0.1897992044687271f, 0.1974248886108398f, 1.0f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.1545050293207169f, 0.1545048952102661f, 0.1545064449310303f, 1.0f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.1414651423692703f, 0.1629818230867386f, 0.2060086131095886f, 1.0f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.1072951927781105f, 0.107295036315918f, 0.1072961091995239f, 1.0f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
    style.Colors[ImGuiCol_Separator] = ImVec4(0.1293079704046249f, 0.1479243338108063f, 0.1931330561637878f, 1.0f);
    style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.1568627506494522f, 0.1843137294054031f, 0.250980406999588f, 1.0f);
    style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.1568627506494522f, 0.1843137294054031f, 0.250980406999588f, 1.0f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.1459212601184845f, 0.1459220051765442f, 0.1459227204322815f, 1.0f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.9725490212440491f, 1.0f, 0.4980392158031464f, 1.0f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.999999463558197f, 1.0f, 0.9999899864196777f, 1.0f);
    style.Colors[ImGuiCol_Tab] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
    style.Colors[ImGuiCol_TabHovered] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
    style.Colors[ImGuiCol_TabActive] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
    style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
    style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.1249424293637276f, 0.2735691666603088f, 0.5708154439926147f, 1.0f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(0.5215686559677124f, 0.6000000238418579f, 0.7019608020782471f, 1.0f);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.03921568766236305f, 0.9803921580314636f, 0.9803921580314636f, 1.0f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.8841201663017273f, 0.7941429018974304f, 0.5615870356559753f, 1.0f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.9570815563201904f, 0.9570719599723816f, 0.9570761322975159f, 1.0f);
    style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
    style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
    style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
    style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.09803921729326248f, 0.105882354080677f, 0.1215686276555061f, 1.0f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.9356134533882141f, 0.9356129765510559f, 0.9356223344802856f, 1.0f);
    style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.266094446182251f, 0.2890366911888123f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 0.501960813999176f);
    style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 0.501960813999176f);

    ImGui_ImplWin32_Init(Hwnd);
    ImGui_ImplDX11_Init(d3d_device, device_context);
}


//bool Overlay::CreateOverlay()
//{
//    // Get ClientSize
//    GetClientRect(GlobalsConfig.GameHwnd, &GlobalsConfig.GameRect);
//    ClientToScreen(GlobalsConfig.GameHwnd, &GlobalsConfig.GamePoint);
//
//    // Create Overlay
//    wc = { sizeof(WNDCLASSEXA), 0, WndProc, 0, 0, NULL, NULL, NULL, NULL, Title, Class, NULL };
//    RegisterClassExA(&wc);
//    /*Hwnd = CreateWindowExA(WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW | WS_EX_TOPMOST, wc.lpszClassName, wc.lpszMenuName, WS_POPUP | WS_VISIBLE, GlobalsConfig.GamePoint.x, GlobalsConfig.GamePoint.y, GlobalsConfig.GameRect.right, GlobalsConfig.GameRect.bottom, NULL, NULL, wc.hInstance, NULL);*/
//    SetLayeredWindowAttributes(Hwnd, RGB(0, 0, 0), 255, LWA_ALPHA);
//    MARGINS margin = { -1 };
//    DwmExtendFrameIntoClientArea(Hwnd, &margin);
//
//    if (!CreateDeviceD3D(Hwnd))
//    {
//        CleanupDeviceD3D();
//        UnregisterClassA(wc.lpszClassName, wc.hInstance);
//
//        return false;
//    }
//
//    // work
//    ShowWindow(Hwnd, SW_SHOWDEFAULT);
//    UpdateWindow(Hwnd);
//
//    // imgui work in bottom
//
//
//    IMGUI_CHECKVERSION();
//
//    ImGui::CreateContext();
//    ImGuiIO& io = ImGui::GetIO(); (void)io;
//    io.IniFilename = nullptr;
//    io.LogFilename = nullptr;
//
//    Logging::debug_print("load the imgui styles");
//    LoadStyle();
//
//    ImGui_ImplWin32_Init(Hwnd);
//
//    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
//
//    return true;
//}

//auto Overlay::ClientSize() -> void {
//    GetClientRect(GlobalsConfig.GameHwnd, &GlobalsConfig.GameRect);
//    ClientToScreen(GlobalsConfig.GameHwnd, &GlobalsConfig.GamePoint);
//}

bool Overlay::InitDevice() {
    DXGI_SWAP_CHAIN_DESC vSwapChainDesc;
    ZeroMemory(&vSwapChainDesc, sizeof(vSwapChainDesc));
    vSwapChainDesc.BufferCount = 2;
    vSwapChainDesc.BufferDesc.Width = 0;
    vSwapChainDesc.BufferDesc.Height = 0;
    vSwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    vSwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    vSwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    vSwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    vSwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    vSwapChainDesc.OutputWindow = Hwnd;
    vSwapChainDesc.SampleDesc.Count = 1;
    vSwapChainDesc.SampleDesc.Quality = 0;
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
    /*swap_chain->CreateRenderTargetView(vBackBuffer, NULL, &render_target_view);*/
    // todo: error here if it can't get the backbuffer of the render target
	vBackBuffer->Release();
}

bool Overlay::ApplyWindowStyles() {
 /*   MARGINS margins = { -1 };
    margins.cyBottomHeight = margins.cyTopHeight = margins.cxLeftWidth = margins.cxRightWidth = -1;
    DwmExtendFrameIntoClientArea(Hwnd, &margins);
    SetLayeredWindowAttributes(Hwnd, 0x000000, 0xFF, 0x02);*/
    auto getInfo = GetWindowLongA(Hwnd, -20);
    auto changeAttributes = SetWindowLongA(Hwnd, -20, (LONG_PTR)(getInfo | 0x20));
    SetLayeredWindowAttributes(Hwnd, 0x000000, 0xFF, 0x02);

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

	LoadStyle();
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

bool IsKeyDown(int VK)
{
    return (GetAsyncKeyState(VK) & 0x8000) != 0;
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
    if (GlobalsConfig.StreamProof && Flag == WDA_NONE)
        SetWindowDisplayAffinity(Hwnd, WDA_EXCLUDEFROMCAPTURE);
    else if (!GlobalsConfig.StreamProof && Flag == WDA_EXCLUDEFROMCAPTURE)
        SetWindowDisplayAffinity(Hwnd, WDA_NONE);

    HWND ForegroundWindow = GetForegroundWindow();
    LONG TmpLong = GetWindowLong(Hwnd, GWL_EXSTYLE);

   /* if (GlobalsConfig.ShowMenu && MenuStyle != TmpLong)
        SetWindowLong(Hwnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TOPMOST);
    else if (!GlobalsConfig.ShowMenu && ESPStyle != TmpLong)
        SetWindowLong(Hwnd, GWL_EXSTYLE, WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TOPMOST);*/

    static bool menu_key = false;
    if (IsKeyDown(GlobalsConfig.MenuKey) && !menu_key)
    {
        GlobalsConfig.ShowMenu = !GlobalsConfig.ShowMenu;

        if (GlobalsConfig.ShowMenu && ForegroundWindow != Hwnd)
            SetForegroundWindow(Hwnd);
     /*   else if (!GlobalsConfig.ShowMenu && ForegroundWindow != CheckHwnd)
            SetForegroundWindow(CheckHwnd);*/

        menu_key = true;
    }
    else if (!IsKeyDown(GlobalsConfig.MenuKey) && menu_key)
    {
        menu_key = false;
    }

  /*  RECT TmpRect{};
    POINT TmpPoint{};
    GetClientRect(CheckHwnd, &TmpRect);
    ClientToScreen(CheckHwnd, &TmpPoint);*/
    
  /*  if (TmpRect.left != GlobalsConfig.GameRect.left || TmpRect.bottom != GlobalsConfig.GameRect.bottom || TmpRect.top != GlobalsConfig.GameRect.top || TmpRect.right != GlobalsConfig.GameRect.right || TmpPoint.x != GlobalsConfig.GamePoint.x || TmpPoint.y != GlobalsConfig.GamePoint.y)
{*/
   

	//Logging::debug_print("game rect changed");
 //   /*GlobalsConfig.GameRect = TmpRect;
 //   GlobalsConfig.GamePoint = TmpPoint;*/
 //   RECT TmpRect{ 0 };
 //   GetClientRect(Hwnd, &TmpRect);
 //   SetWindowPos(Hwnd, HWND_TOPMOST, TmpRect.left, TmpRect.top, TmpRect.right, TmpRect.bottom, SWP_NOREDRAW);

	//RECT rect{ 0 };
 //   GetClientRect(CheckHwnd, &rect);

 //   SetWindowPos(Hwnd, HWND_TOPMOST, rect.left, rect.top, rect.right, rect.bottom, SWP_NOREDRAW);

    //}
 /*   GetClientRect(Hwnd, &rect);
    SetWindowPos(Hwnd, HWND_TOPMOST, TmpPoint.x, TmpPoint.y, GlobalsConfig.GameRect.right, GlobalsConfig.GameRect.bottom, SWP_NOREDRAW);*/

    
}
void Overlay::OverlayLoop() {
    if (!Hwnd) {
        Logging::error_print("cant start overlay loop");
        return;
    }
    while (GlobalsConfig.Run) {
        MSG msg;
        const float clear_color_with_alpha[4] = { 0.f, 0.f, 0.f, 0.f };

        if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }
        RECT rect{ 0 };
        GetClientRect(Hwnd, &rect);
        SetWindowPos(Hwnd, HWND_TOPMOST, rect.left, rect.top, rect.right, rect.bottom, SWP_NOREDRAW);
        //RenderManager("SDL_app");
        RenderManager();
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        float window_width = GetSystemMetrics(SM_CXSCREEN);
        float window_height = GetSystemMetrics(SM_CYSCREEN);
        GlobalsConfig.GameRect.right = window_width;
		GlobalsConfig.GameRect.bottom = window_height;
        // our render cheat
        Cs2::Esp();
        // window_width and window_height
        //float window_width = GetSystemMetrics(SM_CXSCREEN);
        //float window_height = GetSystemMetrics(SM_CYSCREEN);
        ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(window_width / 2.f, window_height / 2.f), GlobalsConfig.Aim_Fov, GlobalsConfig.Fov_color);

        //ImGui::Text("Hello, world!");
        ImGui::Render();
        device_context->OMSetRenderTargets(1, &render_target_view, NULL);
        device_context->ClearRenderTargetView(render_target_view, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        swap_chain->Present(1, 0);
    }
    /*return msg.message != WM_QUIT;*/
}

bool Overlay::InitOverlay(const std::wstring targetName, int overlayMode) {
    // example usage initOverlay for nvidia: FindWindowA("CEF-OSC-WIDGET", "NVIDIA GeForce Overlay");
    // FindWindowA("CEF-OSC-WIDGET", "NVIDIA GeForce Overlay");
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
    if (!InitDevice()) {
		Logging::error_print("cant init device");
        return false;
    }
	if (!ApplyWindowStyles()) {
		Logging::error_print("cant apply window styles");
		return false;
	}
   

}