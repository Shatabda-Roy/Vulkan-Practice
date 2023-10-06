#include "appWnd.h"
#include "appDevice.h"

HWND        g_hWnd;
HINSTANCE   g_hInstance;
bool g_shouldClose = false;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int main () {    
    apparatus::InitWindow _window{g_hInstance, g_hWnd, SW_SHOW, WindowProc};
    apparatus::InitVulkan _vulkan{};
    
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