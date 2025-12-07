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

	// �ε��� Ŭ���� �� ���� ��ư ����ȭ
	if (m_currentStageIndex < 0) m_currentStageIndex = 0;
	if (m_currentStageIndex >= (int)m_buttons.size()) m_currentStageIndex = (int)m_buttons.size() - 1;
	m_currentButton = m_buttons[m_currentStageIndex];
	if (!m_currentButton) return;

	if (GET_KEYDOWN(KEY_TYPE::E)) {
		m_currentButton->m_buttonState = ButtonState::Clicked;
	}
	else if (GET_KEYUP(KEY_TYPE::E)) {
		m_currentButton->Click();
		m_currentButton->m_buttonState = ButtonState::Selected;
	}

	if (GET_KEYUP(KEY_TYPE::DOWN) || GET_KEYUP(KEY_TYPE::S)) {
		if (m_currentStageIndex + 1 >= (int)m_buttons.size()) return;
		if (m_buttons[m_currentStageIndex]) m_buttons[m_currentStageIndex]->m_buttonState = ButtonState::Default;
		++m_currentStageIndex;
		m_currentButton = m_buttons[m_currentStageIndex];
		if (m_currentButton) m_currentButton->m_buttonState = ButtonState::Selected;
	}
	if (GET_KEYUP(KEY_TYPE::UP) || GET_KEYUP(KEY_TYPE::W)) {
		if (m_currentStageIndex - 1 < 0) return;
		if (m_buttons[m_currentStageIndex]) m_buttons[m_currentStageIndex]->m_buttonState = ButtonState::Default;
		--m_currentStageIndex;
		m_currentButton = m_buttons[m_currentStageIndex];
		if (m_currentButton) m_currentButton->m_buttonState = ButtonState::Selected;
	}
}

void ButtonSwitcher::OnOffInput(bool _isOn)
{
	m_isOn = _isOn;
}
