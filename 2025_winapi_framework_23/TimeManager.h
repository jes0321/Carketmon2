#pragma once

class TimeManager
{
	DECLARE_SINGLE(TimeManager);
public:
	void Init();
	void Update();
public:
	float GetDT() const { return m_dT; }
private:
	LARGE_INTEGER m_llPrevCnt = {};
	LARGE_INTEGER m_llCurCnt = {};
	LARGE_INTEGER m_llFrequency = {};

	// DT(Delta Time)
	float m_dT = 0.f;

	// FPS(Freme pre second)
	UINT m_fps = 0;

	UINT m_frameCnt = 0;
	float m_frameTime = 0.f;

};

