#pragma once
#include "Scene.h"
#include "UnitData.h"
#include "ButtonSwitcher.h"

class TreatmentCenterScene :
    public Scene
{
public:
    void Init() override;
    void Update() override;
    void LateUpdate() override;
private:
	ButtonSwitcher* m_buttonSwitcherToChange;
	ButtonSwitcher* m_buttonSwitcherToSelect;
	UnitData* m_unit1;
	UnitData* m_unit2;
	UnitType m_playerType;
	bool m_isCompelet = false;
};

