#pragma once
#include "Scene.h"
class ButtonSwitcher;
class UnitData;
class Texture;
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
    void CalculateLayout(); // 레이아웃 계산 함수 추가

    Texture* m_selectBoxTex = nullptr;
    // UI
    ButtonSwitcher* m_btnManager = nullptr;

    // 후보 유닛
    vector<UnitData*> m_candidates;
    vector<UnitData*> m_selectVec;
    bool m_isSelectionEnabled = true;
    // 커서
    int m_cursor = 0;

    // 레이아웃 기본 파라미터
    int   m_cols = 4;
    int   m_rows = 4;
    float m_tileW = 128.f;
    float m_tileH = 128.f;
    float m_spacingX = 24.f;
    float m_spacingY = 24.f;

    float m_buttonHalfW = 75.f;
    float m_buttonCenterX = (float)(WINDOW_WIDTH - 80.f);
    float m_leftAreaLeftX = 0.f;

    float m_innerPadX = 32.f;
    float m_innerPadY = 24.f;
    float m_bottomMargin = 40.f;
    float m_bgOuterPadX = 40.f;

    // 계산된 레이아웃 값들 (캐시)
    float m_gridWidth = 0.f;
    float m_gridHeight = 0.f;
    float m_startX = 0.f;
    float m_startY = 0.f;
    float m_bCX = 0.f;
    float m_bCY = 0.f;
    float m_bW = 0.f;
    float m_bH = 0.f;
    float m_descBoxLeft = 0.f;
    float m_descBoxWidth = 350.f;
    float m_descBoxTop = 0.f;
    float m_descBoxHeight = 0.f;
    float m_descBoxCenterX = 0.f;
    float m_descBoxCenterY = 0.f;
};