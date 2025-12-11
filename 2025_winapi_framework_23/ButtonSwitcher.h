#pragma once
#include "Object.h"
#include "Button.h"
class ButtonSwitcher :
	public Object
{
public:
	ButtonSwitcher();
	~ButtonSwitcher();
public:
	void Render(HDC _hdc);
	void Update() override;
public:
	void SetWidth() { m_isWidth = true; }
	void SetAvailable(bool _isAvailable) 
	{
		if (_isAvailable)
		{
			m_currentTime = 0;
			m_isNowAvailable = true;
			m_currentButton = m_buttons[0];
			m_currentButton->m_buttonState = ButtonState::Selected;
		}
		else
		{
			m_currentButtonIndex = 0;
		}
		
		m_isAvailable = _isAvailable;
	}
	bool GetAvailable() const { return m_isAvailable; }
	int GetButtonIndex() const { return m_currentButtonIndex; }
	Button* GetCurrentButton() const { return m_currentButton; }
	vector<Button*> GetCurrentButtons() const { return m_buttons; }

	void SetButtons(const vector<Button*>& _buttons)
	{
		m_buttons = _buttons;

		if (!_buttons.empty())
		{
			m_currentButton = m_buttons[0];
			m_currentButton->m_buttonState = ButtonState::Selected;
		}
	}
private:
	vector<Button*> m_buttons;
	Button* m_currentButton = nullptr;

	float m_clickDelay = 0.1f;
	float m_currentTime = 0.1f;

	int m_currentButtonIndex = 0;

	bool m_isAvailable = true;
	bool m_isNowAvailable = false;
	bool m_isWidth = false;
	bool m_isOn = true;
};

