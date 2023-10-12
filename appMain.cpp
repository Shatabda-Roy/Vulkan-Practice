#include "appDevice.h"
HWND        g_hWnd;
bool g_shouldClose = false;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	AllocConsole();
	FILE* fDummy;
	freopen_s(&fDummy, "CONOUT$", "w", stdout);
    freopen_s(&fDummy, "CONOUT$","w",stderr);
    std::cerr.clear();
	std::cout.clear();
    apparatus::InitWindow _window{hInstance, SW_SHOW, WindowProc};
    g_hWnd = _window.g_hWnd;
    apparatus::InitVulkan _vulkan{g_hWnd,hInstance};
    
    MSG msg = { };
    
    while (!g_shouldClose)
    {
        if(PeekMessageW(&msg,g_hWnd,NULL,NULL,PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);    
        }
    }
    return EXIT_SUCCESS;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
    case WM_CLOSE:
        PostQuitMessage(69);
        break;
    case WM_DESTROY:
        g_shouldClose = true;
        DestroyWindow(g_hWnd);
        return EXIT_SUCCESS;
    default:
        break;
    }
    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}