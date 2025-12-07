#include "pch.h"
#include "ButtonSwitcher.h"
#include "InputManager.h"
ButtonSwitcher::ButtonSwitcher()
{

}

ButtonSwitcher::~ButtonSwitcher()
{

}

void ButtonSwitcher::Render(HDC _hdc)
{
	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i]->Render(_hdc);
	}
}

void ButtonSwitcher::Update()
{
	if (m_isAvailable == false)
	{
		for (int i = 0; i < m_buttons.size(); i++)
			m_buttons[i]->m_buttonState = ButtonState::Default;
	}

	if (m_isAvailable == false || m_currentButton == nullptr) return;

	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i]->Update();
	}

	if (GET_KEYDOWN(KEY_TYPE::E))
	{
		m_buttons[m_currentStageIndex]->m_buttonState = ButtonState::Clicked;
	}
	else if (GET_KEYUP(KEY_TYPE::E))
	{
		m_buttons[m_currentStageIndex]->m_buttonState = ButtonState::Selected;
		m_buttons[m_currentStageIndex]->Click();
	}

	if (GET_KEYUP(KEY_TYPE::DOWN) || GET_KEYUP(KEY_TYPE::S))
	{
		if (m_currentStageIndex + 1 >= m_buttons.size()) return;

		++m_currentStageIndex;
		m_buttons[m_currentStageIndex - 1]->m_buttonState = ButtonState::Default;
		m_buttons[m_currentStageIndex]->m_buttonState = ButtonState::Selected;
	}
	if (GET_KEYUP(KEY_TYPE::UP) || GET_KEYUP(KEY_TYPE::W))
	{
		if (m_currentStageIndex - 1 < 0) return;

		--m_currentStageIndex;
		m_buttons[m_currentStageIndex + 1]->m_buttonState = ButtonState::Default;
		m_buttons[m_currentStageIndex]->m_buttonState = ButtonState::Selected;
	}
}
