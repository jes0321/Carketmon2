#pragma once
#include "Scene.h"
#include "Enums.h"

class CardObject;
class CardData;

class BattleScene : public Scene
{
public:
    void Init() override;
    void Update() override;
    void SetCardData(vector<CardData*> _hands);

private:
    void SelectHand();
    UnitType AskTargetUnit(); // 윈도우 기본 대화상자(메시지박스)로 선택

private:
    vector<CardObject*> m_cardObjs;
    int      m_handIndex = 0;
    UIType   m_uiType = UIType::NONE;

    // 마지막 선택 대상
    UnitType m_lastChosenUnit = UnitType::ENEMY;
};

