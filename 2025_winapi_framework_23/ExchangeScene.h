#pragma once
#include "Scene.h"
#include "Text.h"
class ExchangeScene :
    public Scene
{
public:
    void Init() override;
    void Update() override;
private:
	Text* m_textObj = nullptr;
	float m_currentTime = 0.f;
	float m_delayTime = 3.f;
};

