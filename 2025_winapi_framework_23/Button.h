#pragma once
#include "Object.h"
#include "Texture.h"

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
public:
	void SetTexture(Texture* _texture) { m_texture = _texture; }
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
	ButtonState m_buttonState = ButtonState::Default;
	Texture* m_texture = nullptr;
	std::function<void()> m_onClick;
	std::string m_buttonText = "Button 클릭";
};

