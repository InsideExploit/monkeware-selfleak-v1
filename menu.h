#pragma once

bool show_aim_tab = true;
bool show_weapon_tab = false;
bool show_visual_tab = false;
bool show_misc_tab = false;

static LPDIRECT3D9              g_pD3D = NULL;
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

static int draw_menu()
{
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, (_T("Monkehook")), NULL };
    ::RegisterClassEx(&wc);
    HWND hwnd = ::CreateWindow(wc.lpszClassName, (_T("Monkehook")), WS_TILEDWINDOW, 100, 100, 415.5, 428.4, NULL, NULL, wc.hInstance, NULL);

    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 0;
    }

    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    //ImGui style
    ImGui::CustomStyle();

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {

        if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            continue;
        }
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        {
            //Draw here
            ImGui::SetNextWindowSize({ 400, 390 }, ImGuiCond_Always);
            ImGui::SetNextWindowPos(ImVec2(-1, 0));
            ImGui::SetNextWindowCollapsed(false);
            ImGui::Begin(xorstr_(" "), reinterpret_cast<bool*>(true), ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
            ImGui::Dummy({ 0, 1 });
            ImGui::Text(" Monkehook | ");
            ImGui::SameLine();
            if (ImGui::Button(xorstr_(" Aimbot ")))
            {
                show_aim_tab = true;
                show_weapon_tab = false;
                show_visual_tab = false;
                show_misc_tab = false;
            }
            ImGui::SameLine();
            if (ImGui::Button(xorstr_(" Weapon ")))
            {
                show_aim_tab = false;
                show_weapon_tab = true;
                show_visual_tab = false;
                show_misc_tab = false;
            }
            ImGui::SameLine();
            if (ImGui::Button(xorstr_(" Visual ")))
            {
                show_aim_tab = false;
                show_weapon_tab = false;
                show_visual_tab = true;
                show_misc_tab = false;
            }
            ImGui::SameLine();
            if (ImGui::Button(xorstr_("  Misc  ")))
            {
                show_aim_tab = false;
                show_weapon_tab = false;
                show_visual_tab = false;
                show_misc_tab = true;
            }
            ImGui::Dummy({ 0, 5 });
            ImGui::Separator();
            ImGui::NewLine();
            if (show_aim_tab == true)
            {
                ImGui::Checkbox(xorstr_(" Aimbot"), &features::aim_enabled_state);
                ImGui::Dummy({ 0, 1 });
                ImGui::Checkbox(xorstr_(" Team"), &features::team_aim_enabled_state);
                ImGui::Dummy({ 0, 1 });
                ImGui::SliderFloat(xorstr_(" FOV"), &features::aim_fov, 0.f, 3600.f);
                ImGui::Dummy({ 0, 2 });
                ImGui::Combo(" Key##", &key_setting, key_options, IM_ARRAYSIZE(key_options));
                ImGui::Dummy({ 0, 2 });
            }
            if (show_weapon_tab == true)
            {
                ImGui::Checkbox(xorstr_(" Recoil"), &features::nr_enabled_state);
                ImGui::Dummy({ 0, 1 });
                ImGui::SliderFloat(xorstr_(" Recoil##"), &features::recoil, 0.f, 1.f);
                ImGui::Dummy({ 0, 2 });
                ImGui::Checkbox(xorstr_(" Spread"), &features::ns_enabled_state);
                ImGui::Dummy({ 0, 1 });
                ImGui::SliderFloat(xorstr_(" Spread##"), &features::spread, 0.f, 1.f);
                ImGui::Dummy({ 0, 2 });
                ImGui::Checkbox(xorstr_(" Firemode"), &features::firemode_state_enable);
                ImGui::Dummy({ 0, 2 });
                ImGui::Combo(" Key##", &firemode_setting, firemode_options, IM_ARRAYSIZE(firemode_options));
                ImGui::Dummy({ 0, 2 });
            }
            if (show_visual_tab == true)
            {
                ImGui::Checkbox(xorstr_(" Cav ESP"), &features::cav_enabled_state);
                ImGui::Dummy({ 0, 1 });
                ImGui::Checkbox(xorstr_(" Instant ADS"), &features::ads_enabled_state);
                ImGui::Dummy({ 0, 1 });
                ImGui::Checkbox(xorstr_(" Spoof spectate"), &features::spectate_enabled_state);
                ImGui::Dummy({ 0, 1 });
                ImGui::Checkbox(xorstr_(" No flash"), &features::flash_enabled_state);
                ImGui::Dummy({ 0, 1 });
                ImGui::Checkbox(xorstr_(" Fullbright"), &features::fullbright_enabled_state);
                ImGui::Dummy({ 0, 1 });
                ImGui::Checkbox(xorstr_(" Gun FOV"), &features::gfov_enabled_state);
                ImGui::Dummy({ 0, 1 });
                ImGui::SliderFloat(xorstr_(" FOV"), &features::gun_fov, 0.f, 5.f);
                ImGui::Dummy({ 0, 2 });
                ImGui::Checkbox(xorstr_(" Player FOV"), &features::pfov_enabled_state);
                ImGui::Dummy({ 0, 1 });
                ImGui::SliderFloat(xorstr_(" FOV##"), &features::player_fov, 0.f, 5.f);
                ImGui::Dummy({ 0, 2 });
                ImGui::Checkbox(xorstr_(" Glow"), &features::glow_enabled_state);
                ImGui::Dummy({ 0, 2 });
                ImGui::SliderFloat(xorstr_(" R"), &features::glow_RGB[0], -255.f, 255.f);
                ImGui::Dummy({ 0, 1 });
                ImGui::SliderFloat(xorstr_(" G"), &features::glow_RGB[1], -255.f, 255.f);
                ImGui::Dummy({ 0, 1 });
                ImGui::SliderFloat(xorstr_(" B"), &features::glow_RGB[2], -255.f, 255.f);
                ImGui::Dummy({ 0, 2 });
            }
            if (show_misc_tab == true)
            {
                ImGui::Checkbox(xorstr_(" Run and shoot"), &features::ras_enabled_state);
                ImGui::Dummy({ 0, 1 });
                ImGui::Checkbox(xorstr_(" Unlock all"), &features::ua_state_enable);
                ImGui::Dummy({ 0, 1 });
                ImGui::Checkbox(xorstr_(" Ladder launch"), &features::ladder_enabled_state);
                ImGui::Dummy({ 0, 1 });
                ImGui::Checkbox(xorstr_(" Knfe through walls"), &features::knife_wall_enbaled);
                ImGui::Dummy({ 0, 1 });
                ImGui::Checkbox(xorstr_(" Long knife"), &features::knife_enabled_state);
                ImGui::Dummy({ 0, 1 });
                ImGui::SliderFloat(xorstr_(" Reach"), &features::knife_distance, 0.f, 1000.f);
                ImGui::Dummy({ 0, 1 });
                ImGui::Checkbox(xorstr_(" Noclip"), &features::noclip_state_enable);
                ImGui::Dummy({ 0, 1 });
                ImGui::Combo(" Key ##", &noclip_bind, noclip_item, IM_ARRAYSIZE(noclip_item));
                ImGui::Dummy({ 0, 2 });
                ImGui::Checkbox(xorstr_(" Speed"), &features::speed_state_enable);
                ImGui::Dummy({ 0, 1 });
                ImGui::SliderInt(xorstr_(" Speed##"), &features::player_speed, 0, 350);
                ImGui::Dummy({ 0, 2 });
                ImGui::Combo(" Key##", &speed_bind, speed_item, IM_ARRAYSIZE(speed_item));
                ImGui::Dummy({ 0, 2 });
                ImGui::NewLine();
                ImGui::Text("Preformance");
                ImGui::Separator();
                ImGui::NewLine();
                ImGui::SliderInt(xorstr_(" Aim thread sleep"), &sleep_aim, 1, 1000);
            }
            ImGui::End();
            //Draw here
        }
        ImGui::EndFrame();
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x * 255.0f), (int)(clear_color.y * 255.0f), (int)(clear_color.z * 255.0f), (int)(clear_color.w * 255.0f));
        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }
        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
            ResetDevice();
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClass(wc.lpszClassName, wc.hInstance);

    return 0;
}

bool CreateDeviceD3D(HWND hWnd)
{
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        return false;
    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
    if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
        return false;

    return true;
}

void CleanupDeviceD3D()
{
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
    if (g_pD3D) { g_pD3D->Release(); g_pD3D = NULL; }
}

void ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0);
    ImGui_ImplDX9_CreateDeviceObjects();
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            g_d3dpp.BackBufferWidth = LOWORD(lParam);
            g_d3dpp.BackBufferHeight = HIWORD(lParam);
            ResetDevice();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU)
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}