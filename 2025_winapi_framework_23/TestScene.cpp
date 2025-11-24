#include "pch.h"
#include "CardObject.h"
#include "TestScene.h"

void TestScene::Init()
{
	for(int i=0; i < 4; ++i)
	{
		CardObject* card = new CardObject();
		AddObject(card, Layer::CARD);
		card->SetPos(Vec2(100 + i * 120, 300));
		card->SetSize(Vec2(100, 150));
	}
}

void TestScene::UseCard(int index)
{
	
}
