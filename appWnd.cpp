#include "appWnd.h"

apparatus::InitWindow::InitWindow(HINSTANCE hInstance,int nCmdShow,LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)) : m_hInstance{hInstance}, m_nCmdShow{nCmdShow}
{
	MakeWindow(WindowProc);
}

apparatus::InitWindow::~InitWindow()
{
}

void apparatus::InitWindow::MakeWindow(LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam))
{
	WNDCLASSEXW wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = DLGWINDOWEXTRA;
	wc.hInstance = m_hInstance;
	wc.hIcon = NULL;
	wc.hCursor = NULL;
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_className;
	RegisterClassExW(&wc);

	RECT rc = {};
	rc.left = 0;
	rc.top = 0;
	rc.right = m_initClientWidth;
	rc.bottom = m_initClientHeight;

	/* Calculates the required size of the window rectangle, based on the desired client-rectangle size. */
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	/* rc converted into a whole window coords from client coords */

	g_hWnd = CreateWindowExW(WS_EX_OVERLAPPEDWINDOW, wc.lpszClassName, m_windowName,WS_OVERLAPPEDWINDOW , 0, 0, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, m_hInstance, nullptr);
	assert(g_hWnd);
	ShowWindow(g_hWnd, m_nCmdShow);
	UpdateWindow(g_hWnd);
}
