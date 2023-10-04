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

Window::Window(int w ,int h) 
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

	this->width = w;
	this->height = h;

	// rect left and top define how far from left top corner will window show
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

	memory = VirtualAlloc(0, this->height*this->width*8, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);

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

	StretchDIBits(hdc, 0, 0, this->width, this->height, 0, 0, this->width, this->height, this->memory,
		&bitmapInfo, DIB_RGB_COLORS, SRCCOPY);

	while (running)
	{
		if (!ProcesMessages())
		{
			running = false;
		}

	}

}

void* Window::getMemory()
{
	return this->memory;
}

void Window::setMemory(void* memory)
{
	this->memory = memory;
}

void Window::setPixel(int x, int y, u32 color)
{
	int sx = this->width/2 + x;
	int sy = this->height/2 - y;
	u32 *pixel = (u32 *)memory;
	pixel += sy * this->width + sx;
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

void Window::drawRect(int x, int y, int width, int height, u32 color)
{
	for (int i=x; i<width; i++)
	{
		for (int j = y; j < height; j++)
		{
			setPixel(i, j, color);
		}
	}
}
