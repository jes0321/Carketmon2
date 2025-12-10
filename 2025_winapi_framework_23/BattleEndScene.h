#pragma once
#include "Scene.h"
class BattleEndScene : public Scene
{
public :
	void Init() override;
	void Render(HDC _hdc) override;
	void Update() override;
private:
	bool AskTargetUnit(); // 윈도우 기본 대화상자(메시지박스)로 선택
private :
	wstring m_resultText;
	bool m_isWin;
};

