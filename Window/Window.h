#pragma once

#include <Windows.h>
#include <stdint.h>
#include <iostream>

typedef uint32_t u32;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window
{

public:
	Window();
	Window(const Window&) = delete;
	Window& operator =(const Window&) = delete;
	~Window();

	bool ProcesMessages();
	void run();

	void* getMemory();
	void setMemory(void* memory);

	void setPixel(int x, int y, u32 color);
	void setBackground(u32 color);
	void drawRect(int x, int y, int width, int height, u32 color);

private:
	HINSTANCE m_histance;
	HWND m_hwnd;
	BITMAPINFO bitmapInfo;
	void* memory;
	int width;
	int height;

};
