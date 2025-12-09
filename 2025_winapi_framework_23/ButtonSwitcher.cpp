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
	}
	else if (GET_KEYUP(KEY_TYPE::E)) {
		// Click may modify buttons; handle carefully
		m_currentButton->Click();

		// Re-check validity/state after click
		if (m_buttons.empty()) { m_currentButton = nullptr; return; }
		if (m_currentStageIndex < 0) m_currentStageIndex = 0;
		if (m_currentStageIndex >= (int)m_buttons.size()) m_currentStageIndex = (int)m_buttons.size() - 1;
		m_currentButton = m_buttons[m_currentStageIndex];
		if (!m_currentButton) return;

		m_currentButton->m_buttonState = ButtonState::Selected;

		GET_SINGLE(ResourceManager)->Play(L"Btn");
		return;
	}

	if (GET_KEYUP(KEY_TYPE::DOWN) || GET_KEYUP(KEY_TYPE::S)) {
		if (m_currentStageIndex + 1 >= (int)m_buttons.size())
		{
			m_buttons[m_currentStageIndex]->m_buttonState = ButtonState::Default;
			m_currentStageIndex = 0;
			m_currentButton = m_buttons[m_currentStageIndex];
			if (m_currentButton) m_currentButton->m_buttonState = ButtonState::Selected;
			GET_SINGLE(ResourceManager)->Play(L"Btn");
			return;
		}
		if (m_buttons[m_currentStageIndex]) m_buttons[m_currentStageIndex]->m_buttonState = ButtonState::Default;
		++m_currentStageIndex;
		m_currentButton = m_buttons[m_currentStageIndex];
		if (m_currentButton) m_currentButton->m_buttonState = ButtonState::Selected;

		GET_SINGLE(ResourceManager)->Play(L"Btn");
	}
	if (GET_KEYUP(KEY_TYPE::UP) || GET_KEYUP(KEY_TYPE::W)) {
		if (m_currentStageIndex - 1 < 0)
		{
			m_buttons[m_currentStageIndex]->m_buttonState = ButtonState::Default;
			m_currentStageIndex = m_buttons.size() - 1;
			m_currentButton = m_buttons[m_currentStageIndex];
			if (m_currentButton) m_currentButton->m_buttonState = ButtonState::Selected;
			GET_SINGLE(ResourceManager)->Play(L"Btn");
			return;
		}
		if (m_buttons[m_currentStageIndex]) m_buttons[m_currentStageIndex]->m_buttonState = ButtonState::Default;
		--m_currentStageIndex;
		m_currentButton = m_buttons[m_currentStageIndex];
		if (m_currentButton) m_currentButton->m_buttonState = ButtonState::Selected;
		GET_SINGLE(ResourceManager)->Play(L"Btn");

	}
}