#include "pch.h"
#include "SceneManager.h"
#include "TreatmentCenterScene.h"
#include "CombatManager.h"
#include "UnitManager.h"
#include "Button.h"
#include "ButtonSwitcher.h"

void TreatmentCenterScene::Init()
{
    m_buttonSwitcher = new ButtonSwitcher;
    m_buttonSwitcher2 = new ButtonSwitcher;
    AddObject(m_buttonSwitcher, Layer::UI);
    AddObject(m_buttonSwitcher2, Layer::UI);

    //m_buttonSwitcher2->SetAvailable(true);

    vector<Button*> buttons;
    vector<Button*> buttons2;

#pragma region 바꿀 카켓몬 선택 ButtonSwitcher Setting
    for (int i = 0; i < 3; i++)
    {
        Button* obj = new Button;
        obj->SetPos({ WINDOW_WIDTH / 2, (45 * i) + 560 });
        obj->SetSize({ 150,40 });
        AddObject(obj, Layer::DEFAULT);

        switch (i)
        {
        case 0:
        {
            obj->SetOnClick([this]() {
                m_buttonSwitcher2->SetAvailable(true);
                m_buttonSwitcher->SetAvailable(false);
				m_playerType = UnitType::PLAYER1;
                }, "Player1 변경");
        }
        break;
        case 1:
        {
            obj->SetOnClick([this]() {
                m_buttonSwitcher2->SetAvailable(true);
                m_buttonSwitcher->SetAvailable(false);
                m_playerType = UnitType::PLAYER2;
                }, "Player2 변경");
        }
        break;
        case 2:
        {
            obj->SetOnClick([this]() {
                GET_SINGLE(SceneManager)->LoadScene(L"StageSelectScene");
                }, "변경 안하기");
        }
        break;
        default:
            break;
        }

        buttons.push_back(obj);
    }

    m_buttonSwitcher->SetButtons(buttons);
#pragma endregion

#pragma region 가져갈 카켓몬 선택 ButtonSwitcher Setting
    for (int i = 0; i < 3; i++)
    {
        Button* obj = new Button;
        obj->SetPos({ WINDOW_WIDTH / 4, (45 * i) + 560 });
        obj->SetSize({ 150,40 });
        AddObject(obj, Layer::DEFAULT);

        switch (i)
        {
        case 0:
        {
            obj->SetOnClick([this]() {
                }, "카켓몬1로 변경");
        }
        break;
        case 1:
        {
            obj->SetOnClick([this]() {
                }, "카켓몬2로 변경");
        }
        break;
        case 2:
        {
            obj->SetOnClick([this]() {
                m_buttonSwitcher2->SetAvailable(false);
                m_buttonSwitcher->SetAvailable(true);
                }, "취소하기");
        }
        break;
        default:
            break;
        }

        buttons2.push_back(obj);
    }

    m_buttonSwitcher2->SetButtons(buttons);
#pragma endregion
}

void TreatmentCenterScene::Update()
{
	Scene::Update();
	//cout << GET_SINGLE(CombatManager)->GetUnit(UnitType::PLAYER1);
}
