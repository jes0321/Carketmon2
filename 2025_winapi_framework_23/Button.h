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
	void SetOnClick(std::function<void()> func, std::string message = "")
	{
		m_buttonText = message;
		m_onClick = func;
	}

	void Click()
	{
		if (m_onClick)
		{
			cout << m_buttonText << '\n';
			m_onClick(); // 참조한 함수 실행
		}
	}
public:
	std::function<void()> m_onClick;
	ButtonState m_buttonState = ButtonState::Default;
	std::string m_buttonText = "Button 클릭";
};

