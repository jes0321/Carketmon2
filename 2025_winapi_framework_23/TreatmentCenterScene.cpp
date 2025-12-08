    #include "pch.h"
    #include "SceneManager.h"
    #include "TreatmentCenterScene.h"
    #include "UnitData.h"
    #include "UnitObject.h"
    #include "CombatManager.h"
    #include "UnitManager.h"
    #include "Button.h"
    #include "ButtonSwitcher.h"

TreatmentCenterScene::~TreatmentCenterScene()
{
    m_isCompelet = false;
}

void TreatmentCenterScene::Init()
    {
        m_unit1 = GET_SINGLE(UnitManager)->UnitManager::GetUnitRandom();
        m_unit2 = GET_SINGLE(UnitManager)->UnitManager::GetUnitRandom();

        m_buttonSwitcherToChange = new ButtonSwitcher;
        m_buttonSwitcherToSelect = new ButtonSwitcher;
        AddObject(m_buttonSwitcherToChange, Layer::UI);
        AddObject(m_buttonSwitcherToSelect, Layer::UI);

        vector<Button*> buttonsSelect;
        vector<Button*> buttonsChange;

    #pragma region 바꿀 카켓몬 선택 ButtonSwitcher Setting
        for (int i = 0; i < 3; i++)
        {
            Button* obj = new Button;
            obj->SetPos({ WINDOW_WIDTH / 2 + 170, (170 * i) + 160 });
            obj->SetSize({ 150,150 });
            AddObject(obj, Layer::UI);

            switch (i)
            {
            case 0:
            {
                UnitObject* unitObj = GET_SINGLE(CombatManager)->GetUnit(UnitType::PLAYER1);
                obj->SetTexture(unitObj->GetUnitData()->GetTexture());

                obj->SetOnClick([this]() {
                    m_buttonSwitcherToSelect->SetAvailable(true);
                    m_buttonSwitcherToChange->SetAvailable(false);
				    m_playerType = UnitType::PLAYER1;
                    }, "Player1 변경");
            }
            break;
            case 1:
            {
                UnitObject* unitObj = GET_SINGLE(CombatManager)->GetUnit(UnitType::PLAYER2);
                obj->SetTexture(unitObj->GetUnitData()->GetTexture());

                obj->SetOnClick([this]() {
                    m_buttonSwitcherToSelect->SetAvailable(true);
                    m_buttonSwitcherToChange->SetAvailable(false);
                    m_playerType = UnitType::PLAYER2;
                    }, "Player2 변경");
            }
            break;
            case 2:
            {
                obj->SetOnClick([this]() {
                    m_isCompelet = true;
                    }, "변경 안하기");
            }
            break;
            default:
                break;
            }

            buttonsChange.push_back(obj);
        }

        m_buttonSwitcherToChange->SetButtons(buttonsChange);
    #pragma endregion

    #pragma region 가져갈 카켓몬 선택 ButtonSwitcher Setting
        for (int i = 0; i < 3; i++)
        {
            Button* obj = new Button;
            obj->SetPos({ WINDOW_WIDTH / 2 - 170, (170 * i) + 160 });
            obj->SetSize({ 150,150 });
            AddObject(obj, Layer::UI);

            switch (i)
            {
            case 0:
            {
                obj->SetTexture(m_unit1->GetTexture());

                obj->SetOnClick([this]() {
                    }, "카켓몬1로 변경");
            }
            break;
            case 1:
            {
                obj->SetTexture(m_unit2->GetTexture());

                obj->SetOnClick([this]() {
                    }, "카켓몬2로 변경");
            }
            break;
            case 2:
            {
                obj->SetOnClick([this]() {
                    m_buttonSwitcherToSelect->SetAvailable(false);
                    m_buttonSwitcherToChange->SetAvailable(true);
                    }, "취소하기");
            }
            break;
            default:
                break;
            }
            buttonsSelect.push_back(obj);
        }

        m_buttonSwitcherToSelect->SetButtons(buttonsSelect);
    #pragma endregion

        m_buttonSwitcherToSelect->SetAvailable(false);
    }

    void TreatmentCenterScene::Update()
    {
        Scene::Update();

        if (m_isCompelet)
        {
            GET_SINGLE(SceneManager)->LoadScene(L"StageSelectScene");
        }
    }

    void TreatmentCenterScene::LateUpdate()
    {
        Scene::LateUpdate();
    }

