#include "pch.h"
#include "BattleScene.h"
#include "InputManager.h"
#include "CardObject.h"

void BattleScene::Init()
{
    int cardWidth = 40 * 3;
    int cardHeight = 60 * 3;
    int margin = 15;

    for (int i = 0; i < 4; ++i)
    {
        CardObject* cardObj = new CardObject();
        cardObj->SetSize({ (float)cardWidth,(float)cardHeight });

        float centerX = margin + cardWidth * 0.5f + i * (cardWidth + margin);
        float centerY = WINDOW_HEIGHT - cardHeight * 0.5f - margin;

        cardObj->SetPos({ centerX, centerY });

        AddObject(cardObj, Layer::CARD);
        m_cardObjs.push_back(cardObj);
    }
    m_uiType = UIType::HAND;
    m_handIndex = 0;
    if (!m_cardObjs.empty())
        m_cardObjs[0]->SetSelect(true);
}

void BattleScene::Update()
{
    if (m_uiType == UIType::HAND)
        SelectHand();
}

void BattleScene::SelectHand()
{
    if (m_cardObjs.size() < 4) return;

    if (GET_KEYUP(KEY_TYPE::LEFT))
    {
        m_handIndex = (m_handIndex + 3) % 4;
    }
    else if (GET_KEYUP(KEY_TYPE::RIGHT))
    {
        m_handIndex = (m_handIndex + 1) % 4;
    }

    if (GET_KEYUP(KEY_TYPE::LEFT) || GET_KEYUP(KEY_TYPE::RIGHT))
    {
        for (int i = 0; i < 4; ++i)
            m_cardObjs[i]->SetSelect(i == m_handIndex);
    }

    if (GET_KEYUP(KEY_TYPE::C))
    {
        UnitType chosen = AskTargetUnit();
        m_lastChosenUnit = chosen;
    }
}

UnitType BattleScene::AskTargetUnit()
{
    HWND hwndOwner = GetActiveWindow();
    int ret = ::MessageBoxW(
        hwndOwner,
        L"대상 유닛을 선택하세요:\n\nYes : Player1\nNo : Player2\nCancel : Enemy",
        L"유닛 선택",
        MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON1
    );

    switch (ret)
    {
    case IDYES:    return UnitType::PLAYER1;
    case IDNO:     return UnitType::PLAYER2;
    case IDCANCEL: return UnitType::ENEMY;
    default:       return UnitType::ENEMY;
    }
}

void BattleScene::SetCardData(vector<CardData*> _hands)
{
    int n = std::min<int>(4, (int)_hands.size());
    for (int i = 0; i < n && i < (int)m_cardObjs.size(); ++i)
    {
        if (m_cardObjs[i])
            m_cardObjs[i]->SetCardData(_hands[i]);
    }
}
