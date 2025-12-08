#include "pch.h"
#include "ExchangeScene.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "CombatManager.h"
#include "ResourceManager.h"
#include "Image.h"
#include "Text.h"

void ExchangeScene::Init()
{
    m_currentTime = 0;

    Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"button");
    Image* image = new Image(texture);
    image->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 });
    image->SetSize({ 100,100 });
    AddObject(image, Layer::UI);

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

	m_currentTime += fDT;

    if (m_currentTime > m_delayTime)
    {
        if (GET_KEYUP(KEY_TYPE::ENTER))
            GET_SINGLE(SceneManager)->LoadScene(L"StageSelectScene");

        std::wstring text = L"치료 완료! \n 엔터를 눌러 나가기";
        m_textObj->SetText(text);
    }
    else
    {
        std::wstring text = L"치료 중... " + std::to_wstring((int)(m_delayTime - m_currentTime));
        m_textObj->SetText(text);
    }
}
