#include "pch.h"
#include "BattleScene.h"
#include "InputManager.h"
#include "CombatManager.h"
#include "CardObject.h"
#include "Button.h"
#include "ButtonSwitcher.h"

void BattleScene::Init()
{
    int cardWidth = 48 * 4;
    int cardHeight = 64 * 4;
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

    #pragma region ButtonSwitcher Setting
    ButtonSwitcher* buttonSwitcher = new ButtonSwitcher;
    AddObject(buttonSwitcher, Layer::UI);

    vector<Button*> buttons;
    for (int i = 0; i < 3; i++)
    {
        Button* obj = new Button;
        obj->SetPos({ WINDOW_WIDTH - 80, (45 * i) + 560 });
        obj->SetSize({ 150,40 });
        AddObject(obj, Layer::DEFAULT);

        switch (i)
        {
            case 0:
            {
                obj->SetOnClick([this]() {
                    m_uiType = UIType::HAND;
                    OnOffHand(true);
                    }, "UIType::HAND으로 변경");
			}
            break;
            case 1:
            {
                obj->SetOnClick([this]() {
                    m_uiType = UIType::INFO;
                    OnOffHand(false);
                    }, "UIType::INFO으로 변경");
            }
            break;
            case 2:
            {
                obj->SetOnClick([this]() {
                    m_uiType = UIType::DECK;
					OnOffHand(false);
                    }, "UIType::DECK으로 변경");
            }
			break;
        default:
            break;
        }

        buttons.push_back(obj);
    }

    buttonSwitcher->SetButtons(buttons);
    SetCardData();

    #pragma endregion
}

void BattleScene::Update()
{
    Scene::Update();

    if (m_uiType == UIType::HAND)
        SelectHand();
}

void BattleScene::Render(HDC _hdc)
{
	Scene::Render(_hdc);
	GET_SINGLE(CombatManager)->Render(_hdc);
}

void BattleScene::OnOffHand(bool _isOn)
{
    for (auto card : m_cardObjs)
    {
        card->SetActive(_isOn);
	}
}

void BattleScene::SelectHand()
{
    if (m_cardObjs.size() < 4) return;

    if (GET_KEYUP(KEY_TYPE::LEFT)|| GET_KEYUP(KEY_TYPE::A))
    {
        m_handIndex = (m_handIndex + 3) % 4;
    }
    else if (GET_KEYUP(KEY_TYPE::RIGHT)|| GET_KEYUP(KEY_TYPE::D))
    {
        m_handIndex = (m_handIndex + 1) % 4;
    }

    if (GET_KEYUP(KEY_TYPE::LEFT) || GET_KEYUP(KEY_TYPE::RIGHT) || GET_KEYUP(KEY_TYPE::D) || GET_KEYUP(KEY_TYPE::A))
    {
        for (int i = 0; i < 4; ++i)
            m_cardObjs[i]->SetSelect(i == m_handIndex);
    }

    if (GET_KEYUP(KEY_TYPE::C))
    {
        UnitType target = AskTargetUnit();
		GET_SINGLE(CombatManager)->AddAction(target, m_handIndex);
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

void BattleScene::SetCardData()
{
    vector<CardData*> handCards = GET_SINGLE(CombatManager)->GetHandCard();
    int n = std::min<int>(4, (int)handCards.size());
    for (int i = 0; i < n && i < (int)m_cardObjs.size(); ++i)
    {
        if (m_cardObjs[i])
            m_cardObjs[i]->SetCardData(handCards[i]);
    }
}
