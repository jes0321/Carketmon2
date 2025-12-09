#include "pch.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "Image.h"
#include "ResourceManager.h"
#include "Button.h"
#include "ButtonSwitcher.h"
#include "Core.h"
void TitleScene::Init()
{
	float xHarf = WINDOW_WIDTH / 2.f;
	float yHarf = WINDOW_HEIGHT / 2.f;
	
	{
		Image* titleImage = new Image;
		titleImage->SetPos({ xHarf, yHarf - 200 });
		titleImage->SetSize({ 760.f, 196.f });
		titleImage->SetTexture(GET_SINGLE(ResourceManager)->GetTexture(L"Fireball"));
		AddObject(titleImage, Layer::UI);
	}

	ButtonSwitcher*  btnSwitcher = new ButtonSwitcher;
	AddObject(btnSwitcher, Layer::UI);

	vector<Button*> buttons;
	for (int i = 0; i < 2; i++)
	{
		Button* obj = new Button;
		obj->SetPos({ xHarf, (50 * i) + yHarf+200 });
		obj->SetSize({ 150,40 });
		AddObject(obj, Layer::UI);

		switch (i)
		{
		case 0:
		{

			obj->SetButtonType(UIType::START);
			obj->SetOnClick([this]() {
				m_isWait = true;
				}, "시작");
		}
		break;
		case 1:
		{
			obj->SetButtonType(UIType::CANCEL);
			obj->SetOnClick([this]() {
				GET_SINGLE(Core)->ExitGame();
				}, "취소");
		}
		break;
		}

		buttons.push_back(obj);
	}

	btnSwitcher->SetButtons(buttons);
}

void TitleScene::Update()
{
	Scene::Update();
	if (m_isWait == false) return;
	m_timer += fDT;
	if (m_timer >= m_delayTime)
	{
		GET_SINGLE(SceneManager)->LoadScene(L"StartScene");
		m_timer = 0;
	}
}
