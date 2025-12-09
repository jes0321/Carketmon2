#pragma once
#include "Scene.h"
class TitleScene : public Scene
{
public:
	void Init() override;
	void Update() override;
private:
	bool m_isWait = false;
	float m_timer = 0;
	float m_delayTime = 0.1f;
};

