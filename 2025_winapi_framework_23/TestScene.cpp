#include "pch.h"
#include "TestScene.h"
#include "Enemy.h"
void TestScene::Init()
{
	for (UINT i = 0; i < 100; ++i)
		Spawn<Enemy>(Layer::ENEMY, { rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT }, { 50.f,50.f });
}

void TestScene::Update()
{
	Scene::Update();
}

void TestScene::Render(HDC _hdc)
{
	Scene::Render(_hdc);
}
