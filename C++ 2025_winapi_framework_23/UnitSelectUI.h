#pragma once
#include "Object.h"
class UnitData;

class UnitSelectUI : public Object
{
public:
    // 렌더/업데이트
    void Render(HDC _hdc) override;
    void Update() override;

    // 데이터 주입/조회
    void SetCandidates(const vector<UnitData*>& candidates) { m_candidates = candidates; ClampCursor(); }
    const vector<UnitData*>& GetSelected() const { return m_selected; }
    void ClearSelection() { m_selected.clear(); m_selectionEnabled = true; }

    // 입력/선택 토글
    void SetSelectionEnabled(bool on) { m_selectionEnabled = on; }
    bool IsSelectionEnabled() const { return m_selectionEnabled; }

    // 레이아웃 설정
    void SetGrid(int cols, int rows) { m_cols = cols; m_rows = rows; ClampCursor(); }
    void SetTile(float w, float h) { m_tileW = w; m_tileH = h; }
    void SetSpacing(float x, float y) { m_spacingX = x; m_spacingY = y; }
    void SetLeftArea(float buttonCenterX, float buttonHalfW) { m_buttonCenterX = buttonCenterX; m_buttonHalfW = buttonHalfW; }

private:
    // 내부 헬퍼
    void ClampCursor();
    void RenderBackground(HDC _hdc, float startX, float startY, float gridW, float gridH);
    void RenderGrid(HDC _hdc, float startX, float startY);
    void HandleInput();
    void ComputeLayout(float& startX, float& startY, float& gridW, float& gridH) const;

private:
    // 데이터
    vector<UnitData*> m_candidates;
    vector<UnitData*> m_selected;

    // 입력/선택
    int  m_cursor = 0;
    bool m_selectionEnabled = true;

    // 레이아웃 파라미터
    int   m_cols = 4, m_rows = 4;
    float m_tileW = 128.f, m_tileH = 128.f;
    float m_spacingX = 24.f, m_spacingY = 24.f;
    float m_buttonCenterX = (float)(WINDOW_WIDTH - 80.f);
    float m_buttonHalfW = 75.f;
    float m_leftAreaLeftX = 0.f;
    float m_bottomMargin = 40.f;
    float m_innerPadX = 32.f, m_innerPadY = 24.f;
    float m_bgOuterPadX = 40.f;
}