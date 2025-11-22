#pragma once
#include "Scene.h"
class TestScene : public Scene
{
public:
	// Scene을(를) 통해 상속됨
	void Init() override;
	void Update() override;
	void Render(HDC _hdc) override;
};


// 미션: 첫 씬은 DevScene입니다.
// 여기서 Enter 키가 눌리면 TestScene으로 바뀌게 하시고,
// TestScene에는 한 100개 정도의 Enemy클래스를 파서
// 무작위의 색깔로 렌더링 되게 해보세요.
