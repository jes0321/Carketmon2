#pragma once
#include "Object.h"

class CardData;
class Texture;

class DeckUIObj : public Object
{
public:
    DeckUIObj();
    void Render(HDC _hdc) override;
    void Update() override;
    void SetCards(const vector<CardData*>& cards) { m_cards = cards; }

    void SetLayout(int cols, int rows) { m_cols = cols; m_rows = rows; }
    void SetSpacing(float x, float y) { m_spacingX = x; m_spacingY = y; }

private:
    void CalcCardSize(const Vec2& areaSize, float& outW, float& outH) const;
    Vec2 CalcCardPos(const Vec2& areaCenter, const Vec2& areaSize, float cardW, float cardH, int col, int row) const;

private:
	Texture* m_selectBox = nullptr;
    vector<CardData*> m_cards;

    int   m_cols     = 8;
    int   m_rows     = 2;
    float m_spacingX = 12.f;
    float m_spacingY = 12.f;

    // 선택 상태
    int   m_selected = 0; // 0..(m_cols*m_rows-1)
};

