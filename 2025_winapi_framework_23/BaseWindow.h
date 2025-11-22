#pragma once
class BaseWindow
{
public:
	BaseWindow();
	~BaseWindow();
public:
	int Run(HINSTANCE hInstance, int nCmdShow);
private:
	ATOM MyRegisterClass();
	void createWindow();
	void showWindow(int nCmdShow);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	int MessageLoop();
private:
	HINSTANCE m_hInst;
	HWND	  m_hWnd;
};

