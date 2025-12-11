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
    m_currentTime = 0;

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

	int buttonLeftX1 = WINDOW_WIDTH / 2 - 170;
	int buttonLeftX2 = WINDOW_WIDTH / 2 - 370;

#pragma region 바꿀 카켓몬 선택 ButtonSwitcher Setting
    for (int i = 0; i < 3; i++)
    {
        Button* obj = new Button;
        obj->SetPos({ buttonLeftX1, (170 * i) + 160 });
        obj->SetSize({ 150,150 });
        obj->SetStateTexture(texDefault, texClick, texSelect);
        AddObject(obj, Layer::UI);

        switch (i)
        {
        case 0:
        {
            Image* image = new Image();
            image->SetPos({ buttonLeftX1, (170 * i) + 160 });
            image->SetSize({ 130,130 });
            AddObject(image, Layer::UI);

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
            Image* image = new Image();
            image->SetPos({ buttonLeftX1, (170 * i) + 160 });
            image->SetSize({ 130,130 });
            AddObject(image, Layer::UI);

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
            Texture* clickTexture = GET_SINGLE(ResourceManager)->GetTexture(L"Button_SquareExit_Click");
            Texture* defaultTexture = GET_SINGLE(ResourceManager)->GetTexture(L"Button_SquareExit_Default");
            Texture* selectTexture = GET_SINGLE(ResourceManager)->GetTexture(L"Button_SquareExit_Select");
            obj->SetStateTexture(defaultTexture, clickTexture, selectTexture);
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
        obj->SetPos({ buttonLeftX2, (170 * i) + 160 });
        obj->SetSize({ 150,150 });
        obj->SetStateTexture(texDefault, texClick, texSelect);
        AddObject(obj, Layer::UI);

        switch (i)
        {
        case 0:
        {
            Image* image = new Image();
            image->SetPos({ buttonLeftX2, (170 * i) + 160 });
            image->SetSize({ 130,130 });
            AddObject(image, Layer::UI);

            image->SetTexture(m_unit1->GetTexture());

            obj->SetOnClick([this]() {
                m_isCompelet = true;
				GET_SINGLE(CombatManager)->SetUnitData(m_playerType, m_unit1);
                }, "카켓몬1로 변경");
        }
        break;
        case 1:
        {
            Image* image = new Image();
            image->SetPos({ buttonLeftX2, (170 * i) + 160 });
            image->SetSize({ 130,130 });
            AddObject(image, Layer::UI);

            image->SetTexture(m_unit2->GetTexture());

            obj->SetOnClick([this]() {
                m_isCompelet = true;
                GET_SINGLE(CombatManager)->SetUnitData(m_playerType, m_unit1);
                }, "카켓몬2로 변경");
        }
        break;
        case 2:
        {
			Texture* clickTexture = GET_SINGLE(ResourceManager)->GetTexture(L"Button_SquareCancel_Click");
			Texture* defaultTexture = GET_SINGLE(ResourceManager)->GetTexture(L"Button_SquareCancel_Default");
			Texture* selectTexture = GET_SINGLE(ResourceManager)->GetTexture(L"Button_SquareCancel_Select");
            obj->SetStateTexture(defaultTexture, clickTexture, selectTexture);
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

    Image* descBgImage = new Image;
    descBgImage->SetTexture(GET_SINGLE(ResourceManager)->GetTexture(L"CarketmonStatWindow"));
    descBgImage->SetSize({ m_descBoxWidth, m_descBoxHeight });
    descBgImage->SetPos({ (float)WINDOW_WIDTH / 2 + 300, m_descBoxCenterY - 30 });
    AddObject(descBgImage, Layer::BACKGROUND);

    Text* text = new Text(L"");
    text->SetPos({ WINDOW_WIDTH / 2 - 270, WINDOW_HEIGHT / 2 + 320 });
    text->SetSize({ 300,100 });
    AddObject(text, Layer::UI);
    m_changeText = text;
}

    void TreatmentCenterScene::Update()
    {
        Scene::Update();


        if (m_isCompelet)
        {
            m_currentTime += fDT;

            if(m_delayTime < m_currentTime)
                GET_SINGLE(SceneManager)->LoadScene(L"StageSelectScene");
        }

        if (m_buttonSwitcherToChange->GetAvailable())
        {
            if (m_buttonSwitcherToChange->GetButtonIndex() == 0)
                m_currentUnit = GET_SINGLE(CombatManager)->GetUnit(UnitType::PLAYER1)->GetUnitData();
            else if (m_buttonSwitcherToChange->GetButtonIndex() == 1)
                m_currentUnit = GET_SINGLE(CombatManager)->GetUnit(UnitType::PLAYER2)->GetUnitData();
        }
        else if (m_buttonSwitcherToSelect->GetAvailable())
        {
            if (m_buttonSwitcherToSelect->GetButtonIndex() == 0)
                m_currentUnit = m_unit1;
            else if (m_buttonSwitcherToSelect->GetButtonIndex() == 1)
				m_currentUnit = m_unit2;
        }

        std::wstring pokemonName = GET_SINGLE(CombatManager)->GetUnit(m_playerType)->GetUnitData()->GetName();
        std::wstring combinedText = L"현재 바꿀 카켓몬 : " + pokemonName;

        m_changeText->SetText(combinedText);
    }

    void TreatmentCenterScene::Render(HDC _hdc)
    {
		Scene::Render(_hdc);    

        if (m_currentUnit != nullptr) {
            UnitData* currentUnit = m_currentUnit;
            if (currentUnit) {
                GDISelector fontSel(_hdc, FontType::PIXEL_BIG);
                SetBkMode(_hdc, TRANSPARENT);
                SetTextColor(_hdc, RGB(220, 220, 220));

                std::wstring description = currentUnit->GetDescription();

                // 줄 분리
                std::vector<std::wstring> lines;
                size_t start = 0;
                while (true) {
                    size_t p = description.find(L'\n', start);
                    if (p == std::wstring::npos) {
                        lines.push_back(description.substr(start));
                        break;
                    }
                    lines.push_back(description.substr(start, p - start));
                    start = p + 1;
                }

                const int padding = 20;
                const int lineSpacing = 20;

                RECT tempRect = { 0, 0, static_cast<LONG>(m_descBoxWidth - padding * 2), 0 };
                LONG curY = static_cast<LONG>(m_descBoxTop + padding);

                for (const auto& line : lines) {
                    RECT calc = tempRect;
                    DrawTextW(_hdc, line.c_str(), -1, &calc, DT_LEFT | DT_TOP | DT_WORDBREAK | DT_NOPREFIX | DT_CALCRECT);
                    LONG lineHeight = calc.bottom - calc.top;

                    RECT lineRect;
                    lineRect.left = static_cast<LONG>(m_descBoxLeft + padding + 100);
                    lineRect.right = static_cast<LONG>(m_descBoxLeft + m_descBoxWidth - padding + 100);
                    lineRect.top = curY;
                    lineRect.bottom = curY + lineHeight;

                    DrawTextW(_hdc, line.c_str(), -1, &lineRect, DT_LEFT | DT_TOP | DT_WORDBREAK | DT_NOPREFIX);

                    curY += lineHeight + lineSpacing;
                }
            }
        }

        SetTextColor(_hdc, RGB(0, 0, 0));
    }

    void TreatmentCenterScene::LateUpdate()
    {
        Scene::LateUpdate();
    }

