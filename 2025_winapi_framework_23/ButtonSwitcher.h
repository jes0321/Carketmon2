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
	void SetButtons(const vector<Button*>& _buttons)
	{
		m_buttons = _buttons;

		if (!_buttons.empty())
		{
			m_currentButton = m_buttons[0];
			m_currentButton->m_buttonState = ButtonState::Selected;
		}
	}
	void Render(HDC _hdc);
	void Update() override;
	void OnOffInput(bool _isOn);
private:
	bool m_isOn = true;
	vector<Button*> m_buttons;
	Button* m_currentButton = nullptr;
	int m_currentStageIndex = 0;
};

