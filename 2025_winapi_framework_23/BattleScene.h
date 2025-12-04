#pragma once
#include "Scene.h"
#include "Enums.h"

class CardObject;
class CardData;
class DescriptionText;
class BattleScene : public Scene
{
public:
    void Init() override;
    void Update() override;
	void Render(HDC _hdc) override;
	void Release() override;
    void SetCardData();

private:
	void OnOffHand(bool _isOn);
    void SelectHand();
    UnitType AskTargetUnit(); // 윈도우 기본 대화상자(메시지박스)로 선택

private:
	DescriptionText* m_descriptionText = nullptr;
    vector<CardObject*> m_cardObjs;
    int      m_handIndex = 0;
    UIType   m_uiType = UIType::NONE;
};

