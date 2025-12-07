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

}

void ButtonSwitcher::Update()
{
	if (m_isAvailable == false || m_currentButton == nullptr) return;

	if (GET_KEYDOWN(KEY_TYPE::E))
	{
		m_buttons[m_currentStageIndex]->m_buttonState = ButtonState::Clicked;
	}
	else if (GET_KEYUP(KEY_TYPE::E))
	{
		m_buttons[m_currentStageIndex]->Click();
		m_buttons[m_currentStageIndex]->m_buttonState = ButtonState::Selected;
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
