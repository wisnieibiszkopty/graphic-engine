#include "Window.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

Window::Window() 
	: m_histance(GetModuleHandle(nullptr))
{
	const wchar_t* CLASS_NAME = L"Graphic engine";

	WNDCLASS wndClass = {};
	wndClass.lpszClassName = CLASS_NAME;
	wndClass.hInstance = m_histance;
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.lpfnWndProc = WindowProc;

	RegisterClass(&wndClass);

	DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

	this->width = 1600;
	this->height = 900;

	RECT rect;
	rect.left = 100;
	rect.top = 100;
	rect.right = rect.left + this->width;
	rect.bottom = rect.top + this->height;

	AdjustWindowRect(&rect, style, false);

	m_hwnd = CreateWindowEx(
		0, CLASS_NAME, L"Graphic Engine", style,
		rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
		NULL, NULL, m_histance, NULL
	);

	ShowWindow(m_hwnd, SW_SHOW);

	memory = VirtualAlloc(0, this->height*this->width*4, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);

	this->bitmapInfo.bmiHeader.biSize = sizeof(this->bitmapInfo.bmiHeader);
	this->bitmapInfo.bmiHeader.biWidth = this->width;
	// Negative biHeight makes top left as the coordinate system origin. Otherwise it's bottom left.
	this->bitmapInfo.bmiHeader.biHeight = -this->height;
	this->bitmapInfo.bmiHeader.biPlanes = 1;
	this->bitmapInfo.bmiHeader.biBitCount = 32;
	this->bitmapInfo.bmiHeader.biCompression = BI_RGB;
}

Window::~Window() 
{
	const wchar_t* CLASS_NAME = L"Graphic engine";
	UnregisterClass(CLASS_NAME, m_histance);
}

bool Window::ProcesMessages()
{	
	MSG msg = {};

	while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return false;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;
}

void Window::run()
{
	bool running = true;
	HDC hdc = GetDC(m_hwnd);

	while (running)
	{
		if (!ProcesMessages())
		{
			running = false;
		}

		StretchDIBits(hdc, 0, 0, this->width, this->height, 0, 0, this->width, this->height, this->memory,
			&bitmapInfo, DIB_RGB_COLORS, SRCCOPY);

	}

}

void Window::setPixel(int x, int y, u32 color)
{
	u32 *pixel = (u32 *)memory;
	pixel += y * this->width + x;
	*pixel = color;
}

void Window::setBackground(u32 color)
{
	u32* pixel = (u32*)memory;
	for (int i = 0; i < this->width * this->height; i++)
	{
		*pixel++ = color;
	}
}