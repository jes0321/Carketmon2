#pragma once
#include "Scene.h"
#include "ButtonSwitcher.h"

class TreatmentCenterScene :
    public Scene
{
public:
    void Init() override;
    void Update() override;
private:
	ButtonSwitcher* m_buttonSwitcher;
	ButtonSwitcher* m_buttonSwitcher2;
	UnitType m_playerType;
};

