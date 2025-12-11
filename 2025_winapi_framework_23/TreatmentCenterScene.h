#pragma once
#include "Scene.h"
#include "UnitData.h"
#include "ButtonSwitcher.h"
#include "Text.h"

class TreatmentCenterScene :
    public Scene
{
public:
	~TreatmentCenterScene() override;
public:
    void Init() override;
	void Update() override;
    void Render(HDC _hdc) override;
    void LateUpdate() override;
private:
	ButtonSwitcher* m_buttonSwitcherToChange;
	ButtonSwitcher* m_buttonSwitcherToSelect;
	UnitData* m_currentUnit = nullptr;
	UnitData* m_unit1;
	UnitData* m_unit2;
	UnitType m_playerType = UnitType::PLAYER1;

	Text* m_changeText;

	float m_descBoxLeft = 666.f;
	float m_descBoxWidth = 350.f;
	float m_descBoxTop = 112.f;
	float m_descBoxHeight = 564.f;
	float m_descBoxCenterX = 841.f;
	float m_descBoxCenterY = 394.f;

	float m_currentTime;
	float m_delayTime = 0.1f;

	bool m_isCompelet = false;
};

