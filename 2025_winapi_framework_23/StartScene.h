#pragma once
#include "Scene.h"
class ButtonSwitcher;
class UnitData;

class StartScene : public Scene
{
public:
    void Init() override;
    void Update() override;
    void Render(HDC _hdc) override;
    void Release() override;

    void SetSelectionEnabled(bool enabled);
    void CancelSelectAll();
private:
    // UI
    ButtonSwitcher* m_btnManager = nullptr;

    // 데이터
    vector<UnitData*> m_candidates;
    vector<UnitData*> m_selectVec;
	bool m_isSelectionEnabled = true;
    // 선택 커서
    int m_cursor = 0;

    // 레이아웃 상수들을 멤버로 전환(재사용 목적)
    int   m_cols         = 4;
    int   m_rows         = 4;
    float m_tileW        = 128.f;
    float m_tileH        = 128.f;
    float m_spacingX     = 24.f;
    float m_spacingY     = 24.f;

    float m_buttonHalfW  = 75.f;
    float m_buttonCenterX= (float)(WINDOW_WIDTH - 80.f);
    float m_leftAreaLeftX= 0.f;

    float m_innerPadX    = 32.f;
    float m_innerPadY    = 24.f;
    float m_bottomMargin = 40.f;
    float m_bgOuterPadX  = 40.f; // left area width - this
};