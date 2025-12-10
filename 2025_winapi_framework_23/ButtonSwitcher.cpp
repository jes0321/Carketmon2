#include "pch.h"
#include "ButtonSwitcher.h"
#include "InputManager.h"
#include "ResourceManager.h"
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
	if (m_isAvailable == false)
	{
		for (int i = 0; i < m_buttons.size(); i++)
			m_buttons[i]->m_buttonState = ButtonState::Default;
	}

	if (!m_isAvailable) return;
	if (m_buttons.empty()) { m_currentButton = nullptr; return; }

	if (m_currentStageIndex < 0) m_currentStageIndex = 0;
	if (m_currentStageIndex >= (int)m_buttons.size()) m_currentStageIndex = (int)m_buttons.size() - 1;

	Button* newCurrent = m_buttons[m_currentStageIndex];
	if (!newCurrent) { m_currentButton = nullptr; return; }
	m_currentButton = newCurrent;

	if (GET_KEYDOWN(KEY_TYPE::E)) {
		m_currentButton->m_buttonState = ButtonState::Clicked;
		GET_SINGLE(ResourceManager)->Play(L"Btn");
	}
	else if (GET_KEYUP(KEY_TYPE::E)) {
		m_currentButton->m_buttonState = ButtonState::Selected;
		m_currentButton->Click();
		return;
	}

	if (GET_KEYUP(KEY_TYPE::DOWN) || GET_KEYUP(KEY_TYPE::S)||(m_isWidth&& (GET_KEYUP(KEY_TYPE::A)|| GET_KEYUP(KEY_TYPE::LEFT)))) {
		GET_SINGLE(ResourceManager)->Play(L"Btn");
		if (m_currentStageIndex + 1 >= (int)m_buttons.size())
		{
			m_buttons[m_currentStageIndex]->m_buttonState = ButtonState::Default;
			m_currentStageIndex = 0;
			m_currentButton = m_buttons[m_currentStageIndex];
			if (m_currentButton) m_currentButton->m_buttonState = ButtonState::Selected;
			return;
		}
		if (m_buttons[m_currentStageIndex]) m_buttons[m_currentStageIndex]->m_buttonState = ButtonState::Default;
		++m_currentStageIndex;
		m_currentButton = m_buttons[m_currentStageIndex];
		if (m_currentButton) m_currentButton->m_buttonState = ButtonState::Selected;

	}
	if (GET_KEYUP(KEY_TYPE::UP) || GET_KEYUP(KEY_TYPE::W) || (m_isWidth && (GET_KEYUP(KEY_TYPE::D) || GET_KEYUP(KEY_TYPE::RIGHT)))) {
		GET_SINGLE(ResourceManager)->Play(L"Btn");
		if (m_currentStageIndex - 1 < 0)
		{
			m_buttons[m_currentStageIndex]->m_buttonState = ButtonState::Default;
			m_currentStageIndex = m_buttons.size() - 1;
			m_currentButton = m_buttons[m_currentStageIndex];
			if (m_currentButton) m_currentButton->m_buttonState = ButtonState::Selected;
			return;
		}
		if (m_buttons[m_currentStageIndex]) m_buttons[m_currentStageIndex]->m_buttonState = ButtonState::Default;
		--m_currentStageIndex;
		m_currentButton = m_buttons[m_currentStageIndex];
		if (m_currentButton) m_currentButton->m_buttonState = ButtonState::Selected;

	}
}