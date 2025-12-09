    #include "pch.h"
    #include "SceneManager.h"
    #include "TreatmentCenterScene.h"
    #include "UnitData.h"
    #include "UnitObject.h"
    #include "ResourceManager.h"
    #include "CombatManager.h"
    #include "InputManager.h"
    #include "UnitManager.h"
    #include "Button.h"
    #include "Image.h"
    #include "ButtonSwitcher.h"

TreatmentCenterScene::~TreatmentCenterScene()
{
}

void TreatmentCenterScene::Init()
 {
    m_isCompelet = false;

    m_unit1 = GET_SINGLE(UnitManager)->UnitManager::GetUnitRandom();
    m_unit2 = GET_SINGLE(UnitManager)->UnitManager::GetUnitRandom();

    m_buttonSwitcherToChange = new ButtonSwitcher;
    m_buttonSwitcherToSelect = new ButtonSwitcher;
    AddObject(m_buttonSwitcherToChange, Layer::UI);
    AddObject(m_buttonSwitcherToSelect, Layer::UI);

    vector<Button*> buttonsSelect;
    vector<Button*> buttonsChange;

    Texture* texDefault = GET_SINGLE(ResourceManager)->ResourceManager::GetTexture(L"Button_Square_Default");
    Texture* texSelect = GET_SINGLE(ResourceManager)->ResourceManager::GetTexture(L"Button_Square_Select");
    Texture* texClick = GET_SINGLE(ResourceManager)->ResourceManager::GetTexture(L"Button_Square_Click");

#pragma region 바꿀 카켓몬 선택 ButtonSwitcher Setting
    for (int i = 0; i < 3; i++)
    {
        Button* obj = new Button;
        obj->SetPos({ WINDOW_WIDTH / 2 + 170, (170 * i) + 160 });
        obj->SetSize({ 150,150 });
        obj->SetStateTexture(texDefault, texClick, texSelect);
        AddObject(obj, Layer::UI);

        Image* image = new Image();
        image->SetPos({ WINDOW_WIDTH / 2 + 170, (170 * i) + 160 });
        image->SetSize({ 130,130 });
        AddObject(image, Layer::UI);

        switch (i)
        {
        case 0:
        {
            UnitObject* unitObj = GET_SINGLE(CombatManager)->GetUnit(UnitType::PLAYER1);
            image->SetTexture(unitObj->GetUnitData()->GetTexture());

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
            image->SetTexture(unitObj->GetUnitData()->GetTexture());

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
        obj->SetStateTexture(texDefault, texClick, texSelect);
        AddObject(obj, Layer::UI);

        Image* image = new Image();
        image->SetPos({ WINDOW_WIDTH / 2 - 170, (170 * i) + 160 });
        image->SetSize({ 130,130 });
        AddObject(image, Layer::UI);

        switch (i)
        {
        case 0:
        {
            image->SetTexture(m_unit1->GetTexture());

            obj->SetOnClick([this]() {
                m_isCompelet = true;
				GET_SINGLE(CombatManager)->SetUnitData(m_playerType, m_unit1);
                }, "카켓몬1로 변경");
        }
        break;
        case 1:
        {
            image->SetTexture(m_unit2->GetTexture());

            obj->SetOnClick([this]() {
                m_isCompelet = true;
                GET_SINGLE(CombatManager)->SetUnitData(m_playerType, m_unit1);
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
            if(GET_KEYUP(KEY_TYPE::ENTER))
                GET_SINGLE(SceneManager)->LoadScene(L"StageSelectScene");
        }
    }

    void TreatmentCenterScene::LateUpdate()
    {
        Scene::LateUpdate();
    }

