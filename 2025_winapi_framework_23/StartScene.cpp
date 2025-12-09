#include "pch.h"
#include "StartScene.h"
#include "Button.h"
#include "ButtonSwitcher.h"
#include "UnitManager.h"
#include "UnitData.h"
#include "Texture.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "CombatManager.h"
#include "UnitListSys.h"

void StartScene::Init()
{
    m_selectVec.clear();
    m_candidates.clear();

    // 기존 LoadUnitsFromTxt 대신 공용 유틸 사용
    {
        auto names = UnitListSys::ReadNames();
        for (const auto& name : names) {
            UnitData* data = GET_SINGLE(UnitManager)->GetUnit(name);
            if (data) m_candidates.push_back(data);
        }
    }

    m_btnManager = new ButtonSwitcher;
    m_btnManager->SetAvailable(false);
    AddObject(m_btnManager, Layer::UI);

    vector<Button*> buttons;
    for (int i = 0; i < 2; i++)
    {
        Button* obj = new Button;
        obj->SetPos({ WINDOW_WIDTH - 80, (45 * i) + 560 });
        obj->SetSize({ 150,40 });
        AddObject(obj, Layer::DEFAULT);

        switch (i)
        {
        case 0:
        {
            obj->SetButtonType(UIType::CANCEL);
            obj->SetOnClick([this]() {
                CancelSelectAll();
                }, "취소");
        }
        break;
        case 1:
        {
            obj->SetButtonType(UIType::START);
            obj->SetOnClick([this]() {
                // 선택 2개 검증
                if (m_selectVec.size() < 2 || !m_selectVec[0] || !m_selectVec[1]) {
                    SetSelectionEnabled(true);
                    return;
                }
                GET_SINGLE(CombatManager)->SetUnitData(UnitType::PLAYER1, m_selectVec[0]);
                GET_SINGLE(CombatManager)->SetUnitData(UnitType::PLAYER2, m_selectVec[1]);
                GET_SINGLE(SceneManager)->LoadScene(L"StageSelectScene");
                }, "시작");
        }
        break;
        }

        buttons.push_back(obj);
    }

    m_btnManager->SetButtons(buttons);
}


void StartScene::CancelSelectAll()
{
    SetSelectionEnabled(true);
    m_selectVec.clear();
}

void StartScene::Update()
{
    Scene::Update();

    if(m_isSelectionEnabled == false)
		return;
    if (m_candidates.empty()) return;

    const int maxIndex = std::min<int>((int)m_candidates.size(), m_cols * m_rows) - 1;
    if (maxIndex < 0) return;

    // 좌우
    if (GET_KEYUP(KEY_TYPE::LEFT) || GET_KEYUP(KEY_TYPE::A)) {
        int row = m_cursor / m_cols;
        int col = m_cursor % m_cols;
        col = (col + m_cols - 1) % m_cols;
        m_cursor = row * m_cols + col;
        if (m_cursor > maxIndex) m_cursor = maxIndex;
    }
    else if (GET_KEYUP(KEY_TYPE::RIGHT) || GET_KEYUP(KEY_TYPE::D)) {
        int row = m_cursor / m_cols;
        int col = m_cursor % m_cols;
        col = (col + 1) % m_cols;
        m_cursor = row * m_cols + col;
        if (m_cursor > maxIndex) m_cursor = maxIndex;
    }

    // 상하
    if (GET_KEYUP(KEY_TYPE::UP) || GET_KEYUP(KEY_TYPE::W)) {
        int next = m_cursor - m_cols;
        if (next < 0) {
            int lastRowStart = (maxIndex / m_cols) * m_cols;
            next = lastRowStart + (m_cursor % m_cols);
            if (next > maxIndex) next = maxIndex;
        }
        m_cursor = next;
    }
    else if (GET_KEYUP(KEY_TYPE::DOWN) || GET_KEYUP(KEY_TYPE::S)) {
        int next = m_cursor + m_cols;
        if (next > maxIndex) {
            next = (m_cursor % m_cols);
            if (next > maxIndex) next = maxIndex;
        }
        m_cursor = next;
    }

    // 엔터로 선택/해제 + 완료 시 버튼 입력 켜기
    if (GET_KEYUP(KEY_TYPE::ENTER)) {
        UnitData* pick = m_candidates[m_cursor];
        auto it = std::find(m_selectVec.begin(), m_selectVec.end(), pick);
        if (it == m_selectVec.end()) {
            m_selectVec.push_back(pick);
            if (m_selectVec.size() == 2) {
                SetSelectionEnabled(false);
            }
        }
        else {
            m_selectVec.erase(it);
        }
    }
}

void StartScene::Render(HDC _hdc)
{
    Scene::Render(_hdc);

    const float buttonLeftX = m_buttonCenterX - m_buttonHalfW;
    const float leftAreaRightX = buttonLeftX;
    const float leftAreaWidth = leftAreaRightX - m_leftAreaLeftX;

    const float gridWidth = m_cols * m_tileW + (m_cols - 1) * m_spacingX;
    const float gridHeight = m_rows * m_tileH + (m_rows - 1) * m_spacingY;

    const float bgW = (leftAreaWidth - m_bgOuterPadX);
    const float bgH = (gridHeight + m_innerPadY * 2.f);
    const float bgCenterX = m_leftAreaLeftX + bgW * 0.5f;
    const float bgCenterY = WINDOW_HEIGHT - m_bottomMargin - bgH * 0.5f;

    const float startX = (bgCenterX - bgW * 0.5f) + m_innerPadX;
    const float startY = (bgCenterY - bgH * 0.5f) + m_innerPadY;

    // 왼쪽 그리드 박스 (먼저 계산)
    const float padX = 20.f;
    const float padY = 20.f;
    const float bW = gridWidth + padX * 2.f;
    const float bH = gridHeight + padY * 2.f;
    const float bCX = startX + gridWidth * 0.5f;
    const float bCY = startY + gridHeight * 0.5f;

    // 선택 사각형의 오른쪽 모서리
    const float selectionBoxRight = bCX + bW * 0.5f;

    // 우측 설명 박스 (선택 사각형보다 조금 작게)
    const float descBoxLeft = selectionBoxRight + 30.f;
    const float descBoxWidth = 350.f;
    const float descBoxTop = bCY - bH * 0.5f + 60.f; // 위쪽 여백 60px 확보
    const float descBoxHeight = bH - 60.f; // 높이를 60px 줄임
    const float descBoxCenterX = descBoxLeft + descBoxWidth * 0.5f;
    const float descBoxCenterY = descBoxTop + descBoxHeight * 0.5f;

    // 타이틀 텍스트 (설명 박스 위쪽, 이제 충분한 공간 확보됨)
    {
        GDISelector fontSel(_hdc, FontType::PIXEL_BIG);
        SetBkMode(_hdc, TRANSPARENT);
        SetTextColor(_hdc, RGB(50, 50, 50));

        const wchar_t* title = L"캐릭터 선택";
        RECT titleRect;
        titleRect.left = static_cast<LONG>(descBoxLeft);
        titleRect.right = static_cast<LONG>(descBoxLeft + descBoxWidth);
        titleRect.top = static_cast<LONG>(bCY - bH * 0.5f); // 선택 박스 상단과 동일
        titleRect.bottom = static_cast<LONG>(descBoxTop - 5.f); // 설명 박스 위쪽까지

        DrawTextW(_hdc, title, -1, &titleRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
    }

    // 현재 선택중인 유닛 설명 박스
    if (!m_candidates.empty() && m_cursor >= 0 && m_cursor < (int)m_candidates.size()) {
        UnitData* currentUnit = m_candidates[m_cursor];
        if (currentUnit) {
            // 설명 박스 외곽선 렌더링
            {
                GDISelector penSel(_hdc, PenType::BOLD_GRAY);
                GDISelector brushSel(_hdc, BrushType::HOLLOW);
                RECT_RENDER(_hdc, descBoxCenterX, descBoxCenterY, descBoxWidth, descBoxHeight);
            }

            // 설명 텍스트 렌더링 (줄 간격 수동 조정)
            {
                GDISelector fontSel(_hdc, FontType::PIXEL_BIG);
                SetBkMode(_hdc, TRANSPARENT);
                SetTextColor(_hdc, RGB(30, 30, 30));

                std::wstring description = currentUnit->GetDescription();

                // 줄 분리
                std::vector<std::wstring> lines;
                size_t start = 0;
                while (true) {
                    size_t p = description.find(L'\n', start);
                    if (p == std::wstring::npos) {
                        lines.push_back(description.substr(start));
                        break;
                    }
                    lines.push_back(description.substr(start, p - start));
                    start = p + 1;
                }

                const int padding = 20;
                const int lineSpacing = 20; // 줄 간격 추가

                RECT tempRect = { 0, 0, static_cast<LONG>(descBoxWidth - padding * 2), 0 };

                LONG curY = static_cast<LONG>(descBoxTop + padding);

                for (const auto& line : lines) {
                    // 각 줄의 높이 계산
                    RECT calc = tempRect;
                    DrawTextW(_hdc, line.c_str(), -1, &calc, DT_LEFT | DT_TOP | DT_WORDBREAK | DT_NOPREFIX | DT_CALCRECT);
                    LONG lineHeight = calc.bottom - calc.top;

                    // 실제 렌더링
                    RECT lineRect;
                    lineRect.left = static_cast<LONG>(descBoxLeft + padding);
                    lineRect.right = static_cast<LONG>(descBoxLeft + descBoxWidth - padding);
                    lineRect.top = curY;
                    lineRect.bottom = curY + lineHeight;

                    DrawTextW(_hdc, line.c_str(), -1, &lineRect, DT_LEFT | DT_TOP | DT_WORDBREAK | DT_NOPREFIX);

                    curY += lineHeight + lineSpacing; // 줄 간격 추가
                }
            }
        }
    }

    // 왼쪽 그리드 박스
    {
        GDISelector penSel(_hdc, PenType::BOLD_GREEN);
        GDISelector brushSel(_hdc, BrushType::HOLLOW);
        RECT_RENDER(_hdc, bCX, bCY, bW, bH);
    }

    // 유닛 타일 렌더링
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

        if (std::find(m_selectVec.begin(), m_selectVec.end(), ud) != m_selectVec.end()) {
            GDISelector penSel(_hdc, PenType::GREEN);
            GDISelector brushSel(_hdc, BrushType::GREEN);
            RECT_RENDER(_hdc, x, y, m_tileW, m_tileH);
        }
        if (i == m_cursor) {
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

void StartScene::Release()
{
    Scene::Release();
    m_candidates.clear();
    m_selectVec.clear();
    m_btnManager = nullptr;
}

void StartScene::SetSelectionEnabled(bool enabled)
{
    m_isSelectionEnabled = enabled;
    m_btnManager->SetAvailable(!enabled);
}