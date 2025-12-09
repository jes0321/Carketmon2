#include "pch.h"
#include "ExchangeScene.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "CombatManager.h"
#include "UnitObject.h"
#include "ResourceManager.h"
#include "Image.h"
#include "Text.h"

void ExchangeScene::Init()
{
    m_currentTime = 0;

    Texture* texPlayer1 = GET_SINGLE(CombatManager)
        ->GetUnit(UnitType::PLAYER1)->GetUnitData()->GetTexture();
    Texture* texPlayer2 = GET_SINGLE(CombatManager)
        ->GetUnit(UnitType::PLAYER2)->GetUnitData()->GetTexture();

    Image* image = new Image;
    image->SetPos({ WINDOW_WIDTH / 2 + 50, WINDOW_HEIGHT / 2 });
    image->SetSize({ 100,100 });
    image->SetTexture(texPlayer1);
    AddObject(image, Layer::UI);

    Image* image2 = new Image;
    image2->SetPos({ WINDOW_WIDTH / 2 - 50, WINDOW_HEIGHT / 2 });
    image2->SetSize({ 100,100 });
    image2->SetTexture(texPlayer2);
    AddObject(image2, Layer::UI);

    Text* text = new Text(L"");
    text->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 });
    text->SetSize({ 300,100 });
    AddObject(text, Layer::UI);
    m_textObj = text;

	GET_SINGLE(CombatManager)->CombatManager::HealUnit(UnitType::PLAYER1);
	GET_SINGLE(CombatManager)->CombatManager::HealUnit(UnitType::PLAYER2);
}

void ExchangeScene::Update()
{
	Scene::Update();

    if (m_currentTime > m_delayTime)
    {
        std::wstring text = L"치료 완료! \n 엔터를 눌러 나가기";
        m_textObj->SetText(text);

        if (GET_KEYUP(KEY_TYPE::ENTER))
            GET_SINGLE(SceneManager)->LoadScene(L"StageSelectScene");
    }
    else
    {
        m_currentTime += fDT;

        std::wstring text = L"치료 중... " + std::to_wstring((int)(m_delayTime - m_currentTime));
        m_textObj->SetText(text);
    }
}
