#include "pch.h"
#include "UnitInfoObj.h"
#include "UnitStatData.h"

void UnitInfoObj::Render(HDC _hdc)
{
    Vec2 pos = GetPos();
    Vec2 size = GetSize();

    RECT_RENDER(_hdc, pos.x, pos.y, size.x, size.y);

    RECT full;
    full.left   = static_cast<LONG>(pos.x - size.x * 0.5f);
    full.top    = static_cast<LONG>(pos.y - size.y * 0.5f);
    full.right  = static_cast<LONG>(pos.x + size.x * 0.5f);
    full.bottom = static_cast<LONG>(pos.y + size.y * 0.5f);

    // 왼쪽 1/4 영역
    RECT textRect = full;
    LONG width = full.right - full.left;
    textRect.right = textRect.left + (width / 4);

    GDISelector fontUI(_hdc, FontType::BIG_UI);
    SetBkMode(_hdc, TRANSPARENT);
    SetTextColor(_hdc, RGB(20, 20, 20));

    // 3줄 스페이싱을 직접 제어하기 위해 줄별로 DrawTextW 수행
    std::wstring text = GetStatString();

    // 줄 분리
    std::vector<std::wstring> lines;
    {
        size_t start = 0;
        while (true) {
            size_t p = text.find(L'\n', start);
            if (p == std::wstring::npos) {
                lines.push_back(text.substr(start));
                break;
            }
            lines.push_back(text.substr(start, p - start));
            start = p + 1;
        }
    }

    // 각 줄의 높이 계산(DT_CALCRECT) 후, 추가 스페이싱 적용
    const int extraSpacing = 12; // 원하는 추가 스페이싱(px)
    std::vector<LONG> lineHeights;
    LONG maxLineWidth = 0;
    for (auto& line : lines) {
        RECT calc = { 0,0, textRect.right - textRect.left, 0 };
        DrawTextW(_hdc, line.c_str(), -1, &calc, DT_LEFT | DT_TOP | DT_WORDBREAK | DT_NOPREFIX | DT_CALCRECT);
        LONG w = calc.right - calc.left;
        LONG h = calc.bottom - calc.top;
        lineHeights.push_back(h);
        if (w > maxLineWidth) maxLineWidth = w;
    }

    // 전체 텍스트 블록 높이 = 각 줄 높이 + (줄 사이 개수 * extraSpacing)
    LONG totalH = 0;
    for (size_t i = 0; i < lineHeights.size(); ++i) {
        totalH += lineHeights[i];
        if (i + 1 < lineHeights.size()) totalH += extraSpacing;
    }

    // 중앙 배치를 위한 시작 Y 오프셋 계산
    LONG targetH = textRect.bottom - textRect.top;
    LONG startY = textRect.top + (targetH - totalH) / 2;

    // 렌더링 X는 좌측 정렬 기준에서 중앙 정렬 원하면 다음처럼 계산 가능
    // 현재는 좌측 정렬 유지. 중앙 정렬 원할 시 아래 주석 사용:
    // LONG targetW = textRect.right - textRect.left;
    // LONG startXCenter = textRect.left + (targetW - maxLineWidth) / 2;

    LONG curY = startY;
    for (size_t i = 0; i < lines.size(); ++i) {
        RECT lineRect = {
            textRect.left,
            curY,
            textRect.right,
            curY + lineHeights[i]
        };
        DrawTextW(_hdc, lines[i].c_str(), -1, &lineRect, DT_LEFT | DT_TOP | DT_WORDBREAK | DT_NOPREFIX);
        

        Vec2 rectPos((float)textRect.right + 20, (float)((lineRect.top + lineRect.bottom) / 2));
        int spacing = 60;
        int cost = m_statData->GetUpgradeCost(i);

        // 업그레이드된(큰) 사각형들을 왼쪽부터 spacing 간격으로 배치
        for (int j = 0; j < std::abs(cost); ++j) {
            GDISelector rectGDI(_hdc, cost > 0 ? BrushType::BLUE : BrushType::RED);
            RECT_RENDER(_hdc, rectPos.x + j * spacing, rectPos.y, m_bigSize.x, m_bigSize.y);
        }

        // 남은 칸을 기본(작은) 사각형으로 채우면서 동일한 간격으로 배치
        for (int j = std::abs(cost); j < 6; ++j) {
            RECT_RENDER(_hdc, rectPos.x + j * spacing, rectPos.y, m_defaultSize.x, m_defaultSize.y);
        }

        curY += lineHeights[i];
        if (i + 1 < lines.size()) curY += extraSpacing;
    }
}

const wstring UnitInfoObj::GetStatString()
{
    if (m_statData == nullptr)
        return L"";
    std::wstring result;
    result += std::format(L"공격력: {}", m_statData->GetStat(StatType::Attack)) + L"\n";
    result += std::format(L"방어력: {}", m_statData->GetStat(StatType::Defense)) + L"\n";
    result += std::format(L"속도: {}", m_statData->GetStat(StatType::Speed));
    return result;
}
