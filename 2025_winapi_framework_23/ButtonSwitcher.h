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
	void SetAvailable(bool _isAvailable) 
	{
		if (_isAvailable)
		{
			m_currentButton = m_buttons[0];
			m_currentButton->m_buttonState = ButtonState::Selected;
		}
		else
		{
			m_currentStageIndex = 0;
		}

		m_isAvailable = _isAvailable;
	}
	bool GetAvailable() { return m_isAvailable; }
	Button* GetCurrentButton() { return m_currentButton; }
	vector<Button*> GetCurrentButtons() { return m_buttons; }

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
	int m_currentStageIndex = 0;
	bool m_isAvailable = true;
	bool m_isOn = true;
};

