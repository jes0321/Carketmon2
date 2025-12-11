#include "pch.h"
#include "TimeManager.h"
#include "Core.h"
#include "InputManager.h"	
void TimeManager::Init()
{
	// 현재 카운트 시간의 틱을 가져옵니다.
	::QueryPerformanceCounter(&m_llPrevCnt);

	// 초당 카운트 횟수(1000만) 반환
	// 현재 타이머 동작의 주파수를 반환
	::QueryPerformanceFrequency(&m_llFrequency);
}

void TimeManager::Update()
{
	// 현재 카운트 시간의 틱을 가져옵니다.
	::QueryPerformanceCounter(&m_llCurCnt);
	
	// 이전 카운트와 현재 카운트의 차이를 진동수로 나눠서 미세한 DT를 구해온다.
	// Delta Time
	m_dT = (float)(m_llCurCnt.QuadPart - m_llPrevCnt.QuadPart)
		/ (float)(m_llFrequency.QuadPart);
	m_llPrevCnt = m_llCurCnt;

	// FPS
	m_frameCnt++;
	m_frameTime += m_dT;
	if (m_frameTime >= 1.f)
	{
		m_fps = (UINT)(m_frameCnt / m_frameTime);
		m_frameTime = 0.f;
		m_frameCnt = 0;

		wstring strDT = std::to_wstring(m_dT);
		wstring strFPS = std::to_wstring(m_fps);
		//wstring str = L"FPS: " + strFPS + L" DT: " + strDT;
		//::TextOut(GET_SINGLE(Core)->GetMainDC(), 0, 0, str.c_str(), str.length());
		POINT mousepos = GET_MOUSEPOS;
		wstring str = std::format(L"FPS: {0}, DT: {1:.6f}, Mouse: {2}, {3} ", m_fps, m_dT, mousepos.x, mousepos.y);
		//::SetWindowText(GET_SINGLE(Core)->GetHwnd(), str.c_str());
	}


}
