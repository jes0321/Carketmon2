#include "pch.h"
#include "DeckUIObj.h"
#include "CardData.h"
#include "Texture.h"
#include "BattleScene.h"
#include "InputManager.h"
#include "SceneManager.h"

#undef min;
#undef max;

void DeckUIObj::CalcCardSize(const Vec2& areaSize, float& outW, float& outH) const
{
    float maxW_byWidth   = (areaSize.x - m_spacingX * (m_cols - 1)) / m_cols;
    float maxH_byHeight  = (areaSize.y - m_spacingY * (m_rows - 1)) / m_rows;
    float w_from_h       = maxH_byHeight * (3.f / 4.f);
    float cardW          = std::min(maxW_byWidth, w_from_h);
    float cardH          = cardW * (4.f / 3.f);
    outW = floorf(cardW);
    outH = floorf(cardH);
}

Vec2 DeckUIObj::CalcCardPos(const Vec2& areaCenter, const Vec2& areaSize, float cardW, float cardH, int col, int row) const
{
    float leftX = areaCenter.x - areaSize.x * 0.5f;
    float topY  = areaCenter.y - areaSize.y * 0.5f;
    float x = leftX + (cardW * 0.5f) + col * (cardW + m_spacingX);
    float y = topY  + (cardH * 0.5f) + row * (cardH + m_spacingY);
    return { x, y };
}

void DeckUIObj::Update()
{
    Object::Update();

    if (!IsActive()) return;
    const int maxIndex = std::min<int>((int)m_cards.size(), m_cols * m_rows) - 1;
    if (maxIndex < 0) return;

    // 좌/우
    if (GET_KEYUP(KEY_TYPE::LEFT) || GET_KEYUP(KEY_TYPE::A)) {
        m_selected = (m_selected + maxIndex) % (maxIndex + 1); // -1 래핑
    }
    else if (GET_KEYUP(KEY_TYPE::RIGHT) || GET_KEYUP(KEY_TYPE::D)) {
        m_selected = (m_selected + 1) % (maxIndex + 1);
    }

    // 상/하 (열 단위 이동)
    if (GET_KEYUP(KEY_TYPE::UP) || GET_KEYUP(KEY_TYPE::W)) {
        m_selected -= m_cols;
        if (m_selected < 0) m_selected = std::max(0, m_selected + m_cols * m_rows); // 위로 래핑
        if (m_selected > maxIndex) m_selected = maxIndex; // 카드 수가 적을 때 범위 보정
    }
    else if (GET_KEYUP(KEY_TYPE::DOWN) || GET_KEYUP(KEY_TYPE::S)) {
        m_selected += m_cols;
        if (m_selected > maxIndex) m_selected %= (maxIndex + 1); // 아래로 래핑/보정
    }
    BattleScene* scene = GET_SINGLE(SceneManager)->GetBattleScene();
    scene->SetCardDes(m_cards[m_selected]);
}

void DeckUIObj::Render(HDC _hdc)
{
    if (!IsActive()) return;

    Vec2 areaCenter = GetPos();
    Vec2 areaSize   = GetSize();

    float cardW = 0.f, cardH = 0.f;
    CalcCardSize(areaSize, cardW, cardH);

    int maxToDraw = std::min<int>((int)m_cards.size(), m_cols * m_rows);

    for (int i = 0; i < maxToDraw; ++i)
    {
        CardData* cd = m_cards[i];
        if (!cd) continue;

        Texture* tex = cd->GetTexture();
        if (!tex) continue;

        int col = i % m_cols;
        int row = i / m_cols;

        Vec2 pos = CalcCardPos(areaCenter, areaSize, cardW, cardH, col, row);

        LONG srcW = tex->GetWidth();
        LONG srcH = tex->GetHeight();

        ::TransparentBlt(
            _hdc,
            (int)(pos.x - cardW * 0.5f),
            (int)(pos.y - cardH * 0.5f),
            (int)cardW,
            (int)cardH,
            tex->GetTextureDC(),
            0, 0, srcW, srcH,
            RGB(255, 0, 255));

        // 선택 윤곽선
        if (i == m_selected) {
            GDISelector penSel(_hdc, PenType::GREEN);
            GDISelector brushSel(_hdc, BrushType::HOLLOW);
            RECT_RENDER(_hdc, pos.x, pos.y, cardW, cardH);
        }
    }
}
