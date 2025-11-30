#pragma once
#include "Object.h"

enum ButtonState
{
	Default,
	Clicked,
	Selected
};

class Button :
	public Object
{
public:
	Button();
	~Button();
public:
	void Render(HDC _hdc);
	void Update() override;
	void SetOnClick(std::function<void()> func)
	{
		m_onClick = func;
	}

	void Click()
	{
		if (m_onClick) m_onClick();  // 함수 실행
	}
public:
	std::function<void()> m_onClick;
	ButtonState m_buttonState = ButtonState::Default;
};

