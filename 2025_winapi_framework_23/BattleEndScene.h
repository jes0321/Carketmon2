#pragma once
#include "Scene.h"
class BattleEndScene : public Scene
{
public :
	void Init() override;
	void Render(HDC _hdc) override;
private :
	wstring m_resultText;
};

