#pragma once
#include "Scene.h"

class EndingScene : public Scene
{
public:
	EndingScene() = default;
	~EndingScene() = default;

public:
	void Init() override;
	void Update() override;
	void Render(HDC _hdc) override;

private:
	std::wstring m_credit;
	float m_lineSpacing = 60.0f;     // 라인 간격 (픽셀)
	float m_scrollSpeed = 40.0f;     // 스크롤 속도 (픽셀/초)
	float m_currentOffset = 0.0f;    // 현재 스크롤 오프셋
	bool m_isScrolling = true;
	std::vector<std::wstring> m_creditLines;
};

