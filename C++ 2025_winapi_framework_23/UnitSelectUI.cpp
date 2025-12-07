#include "pch.h"
#include "UnitSelectUI.h"
#include "UnitData.h"
#include "Texture.h"
#include "InputManager.h"
#include "GDISelector.h"

void UnitSelectUI::ClampCursor()
{
    int maxIndex = std::min<int>((int)m_candidates.size(), m_cols * m_rows) - 1;
    if (maxIndex < 0) { m_cursor = 0; return; }
    if (m_cursor < 0) m_cursor = 0;
    if (m_cursor > maxIndex) m_cursor = maxIndex;
}

void UnitSelectUI::ComputeLayout(float& startX, float& startY, float& gridW, float& gridH) const
{
    // ¿ÞÂÊ ¿µ¿ª Æø(¹öÆ° ¿ÞÂÊ±îÁö)
    const float leftAreaRightX = m_buttonCenterX - m_buttonHalfW;
    const float leftAreaWidth  = leftAreaRightX - m_leftAreaLeftX;

    gridW = m_cols * m_tileW + (m_cols - 1) * m_spacingX;
    gridH = m_rows * m_tileH + (m_rows - 1) * m_spacingY;

    const float bgW = (leftAreaWidth - m_bgOuterPadX);
    const float bgH = (gridH + m_innerPadY * 2.f);
    const float bgCenterX = m_leftAreaLeftX + bgW * 0.5f;
    const float bgCenterY = WINDOW_HEIGHT - m_bottomMargin - bgH * 0.5f;

    startX = (bgCenterX - bgW * 0.5f) + m_innerPadX;
    startY = (bgCenterY - bgH * 0.5f) + m_innerPadY;
}

void UnitSelectUI::RenderBackground(HDC _hdc, float startX, float startY, float gridW, float gridH)
{
    const float padX = 20.f, padY = 20.f;
    const float bW = gridW + padX * 2.f;
    const float bH = gridH + padY * 2.f;
    const float bCX = startX + gridW * 0.5f;
    const float bCY = startY + gridH * 0.5f;

    GDISelector penSel(_hdc, PenType::BOLD_GREEN);
    GDISelector brushSel(_hdc, BrushType::HOLLOW);
    RECT_RENDER(_hdc, bCX, bCY, bW, bH);
}

void UnitSelectUI::RenderGrid(HDC _hdc, float startX, float startY)
{
    int maxDraw = std::min<int>((int)m_candidates.size(), m_cols * m_rows);
    for (int i = 0; i < maxDraw; ++i) {
        int col = i % m_cols;
        int row = i / m_cols;

        float x = startX + col * (m_tileW + m_spacingX) + m_tileW * 0.5f;
        float y = startY + row * (m_tileH + m_spacingY) + m_tileH * 0.5f;

        UnitData* ud = m_candidates[i];
        if (!ud) continue;
        Texture* tex = ud->GetTexture();
        if (!tex) continue;

        LONG srcW = tex->GetWidth();
        LONG srcH = tex->GetHeight();

        // ¼±ÅÃµÊ(ÃÊ·Ï) À±°û
        if (std::find(m_selected.begin(), m_selected.end(), ud) != m_selected.end()) {
            GDISelector penSel(_hdc, PenType::GREEN);
            GDISelector brushSel(_hdc, BrushType::GREEN);
            RECT_RENDER(_hdc, x, y, m_tileW, m_tileH);
        }
        // ÇöÀç Ä¿¼­(»¡°­)
        if (m_selectionEnabled && i == m_cursor) {
            GDISelector penSel(_hdc, PenType::RED);
            GDISelector brushSel(_hdc, BrushType::HOLLOW);
            RECT_RENDER(_hdc, x, y, m_tileW, m_tileH);
        }

        ::TransparentBlt(
            _hdc,
            (int)(x - m_tileW * 0.5f),
            (int)(y - m_tileH * 0.5f),
            (int)m_tileW,
            (int)m_tileH,
            tex->GetTextureDC(),
            0, 0, srcW, srcH,
            RGB(255, 0, 255));
    }
}

void UnitSelectUI::HandleInput()
{
    if (!m_selectionEnabled) return;
    if (m_candidates.empty()) return;

    int maxIndex = std::min<int>((int)m_candidates.size(), m_cols * m_rows) - 1;
    if (maxIndex < 0) return;

    // ÁÂ¿ì
    if (GET_KEYUP(KEY_TYPE::LEFT) || GET_KEYUP(KEY_TYPE::A)) {
        int row = m_cursor / m_cols;
        int col = m_cursor % m_cols;
        col = (col + m_cols - 1) % m_cols;
        m_cursor = row * m_cols + col;
    } else if (GET_KEYUP(KEY_TYPE::RIGHT) || GET_KEYUP(KEY_TYPE::D)) {
        int row = m_cursor / m_cols;
        int col = m_cursor % m_cols;
        col = (col + 1) % m_cols;
        m_cursor = row * m_cols + col;
    }

    // »óÇÏ
    if (GET_KEYUP(KEY_TYPE::UP) || GET_KEYUP(KEY_TYPE::W)) {
        int next = m_cursor - m_cols;
        if (next < 0) {
            int lastRowStart = (maxIndex / m_cols) * m_cols;
            next = lastRowStart + (m_cursor % m_cols);
        }
        m_cursor = next;
    } else if (GET_KEYUP(KEY_TYPE::DOWN) || GET_KEYUP(KEY_TYPE::S)) {
        int next = m_cursor + m_cols;
        if (next > maxIndex) next = (m_cursor % m_cols);
        m_cursor = next;
    }

    ClampCursor();

    // ¿£ÅÍ ¼±ÅÃ/ÇØÁ¦, ÃÖ´ë 2°³
    if (GET_KEYUP(KEY_TYPE::ENTER)) {
        UnitData* pick = m_candidates[m_cursor];
        auto it = std::find(m_selected.begin(), m_selected.end(), pick);
        if (it == m_selected.end()) {
            m_selected.push_back(pick);
            if (m_selected.size() > 2) m_selected.erase(m_selected.begin());
        } else {
            m_selected.erase(it);
        }
    }
}

void UnitSelectUI::Update()
{
    Object::Update();
    HandleInput();
}

void UnitSelectUI::Render(HDC _hdc)
{
    float startX, startY, gridW, gridH;
    ComputeLayout(startX, startY, gridW, gridH);
    RenderBackground(_hdc, startX, startY, gridW, gridH);
    RenderGrid(_hdc, startX, startY);
}