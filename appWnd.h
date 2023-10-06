#include <iostream>
#include <Windows.h>
#include <assert.h>

namespace apparatus {
    class InitWindow {
    public:
        InitWindow(HINSTANCE hInstance,HWND hWnd,int nCmdShow,LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam));
        ~InitWindow();

        const uint16_t m_initClientWidth = 640;
        const uint16_t m_initClientHeight = 480;
        LPCWSTR m_className = L"Apparatus";
        LPCWSTR m_windowName = L"Shatabda Roy's Program";
    private:
        void MakeWindow(LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam));
        HWND m_hWnd;
        HINSTANCE m_hInstance;
        int m_nCmdShow;
    };
}