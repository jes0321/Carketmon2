#pragma once
//#include "Object.h"
class Core
{
	DECLARE_SINGLE(Core);
public:
	bool Init(HWND _hWnd);
	void GameLoop();
	void CleanUp();
public:
	const HDC& GetMainDC() const { return m_hDC; }
	const HWND& GetHwnd() const { return m_hWnd; }
private:
	void MainUpdate();
	void MainRender();
private:
	HWND m_hWnd;
	HDC  m_hDC;
	//Object m_obj;

	HBITMAP m_hBackBit;
	HDC	    m_hBackDC;
};

//private:
//	Core() {}
//public:
//	static Core* GetInst()
//	{
//		static Core inst;
//		return &inst;
//	}
