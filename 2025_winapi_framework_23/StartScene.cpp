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
#include "Image.h"

void StartScene::CalculateLayout()
{
    const float buttonLeftX = m_buttonCenterX - m_buttonHalfW;
    const float leftAreaRightX = buttonLeftX;
    const float leftAreaWidth = leftAreaRightX - m_leftAreaLeftX;

    m_gridWidth = m_cols * m_tileW + (m_cols - 1) * m_spacingX;
    m_gridHeight = m_rows * m_tileH + (m_rows - 1) * m_spacingY;

    const float bgW = (leftAreaWidth - m_bgOuterPadX);
    const float bgH = (m_gridHeight + m_innerPadY * 2.f);
    const float bgCenterX = m_leftAreaLeftX + bgW * 0.5f;
    const float bgCenterY = WINDOW_HEIGHT - m_bottomMargin - bgH * 0.5f;

    m_startX = (bgCenterX - bgW * 0.5f) + m_innerPadX;
    m_startY = (bgCenterY - bgH * 0.5f) + m_innerPadY;

    const float padX = 20.f;
    const float padY = 20.f;
    m_bW = m_gridWidth + padX * 2.f;
    m_bH = m_gridHeight + padY * 2.f;
    m_bCX = m_startX + m_gridWidth * 0.5f;
    m_bCY = m_startY + m_gridHeight * 0.5f;

    const float selectionBoxRight = m_bCX + m_bW * 0.5f;
    m_descBoxLeft = selectionBoxRight + 30.f;
    m_descBoxTop = m_bCY - m_bH * 0.5f + 60.f;
    m_descBoxHeight = m_bH - 60.f;
    m_descBoxCenterX = m_descBoxLeft + m_descBoxWidth * 0.5f;
    m_descBoxCenterY = m_descBoxTop + m_descBoxHeight * 0.5f;
}

void StartScene::Init()
{
    // 레이아웃 계산 (한 번만 수행)
    CalculateLayout();

	Image* bgImage = new Image;
	bgImage->SetTexture(GET_SINGLE(ResourceManager)->GetTexture(L"TitleBackGround"));
	bgImage->SetSize({ (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT });
	bgImage->SetPos({ WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f });
	AddObject(bgImage, Layer::BACKGROUND);

    // 그리드 배경 이미지
    Image* gridBgImage = new Image;
    gridBgImage->SetTexture(GET_SINGLE(ResourceManager)->GetTexture(L"CarketmonSelectWindow"));
    gridBgImage->SetSize({ m_bW, m_bH });
    gridBgImage->SetPos({ m_bCX, m_bCY });
    AddObject(gridBgImage, Layer::BACKGROUND);

    // 설명 박스 배경 이미지
    Image* descBgImage = new Image;
    descBgImage->SetTexture(GET_SINGLE(ResourceManager)->GetTexture(L"CarketmonStatWindow"));
    descBgImage->SetSize({ m_descBoxWidth, m_descBoxHeight });
    descBgImage->SetPos({ m_descBoxCenterX, m_descBoxCenterY });
    AddObject(descBgImage, Layer::BACKGROUND);

    m_selectVec.clear();
    m_candidates.clear();
    m_selectBoxTex = GET_SINGLE(ResourceManager)->GetTexture(L"CarketmonSelectMark");

    // 유닛 로드
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
        obj->SetSize({ 150, 40 });
        AddObject(obj, Layer::UI);

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
    SetSelectionEnabled(true);
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

    if (m_isSelectionEnabled == false)
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

    // 선택/해제
    if (GET_KEYUP(KEY_TYPE::SPACE)) {
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

    // 타이틀 텍스트
    {
        GDISelector fontSel(_hdc, FontType::PIXEL_BIG);
        SetBkMode(_hdc, TRANSPARENT);
        SetTextColor(_hdc, RGB(255, 255, 255));

        const wchar_t* title = L"캐릭터 선택";
        RECT titleRect;
        titleRect.left = static_cast<LONG>(m_descBoxLeft);
        titleRect.right = static_cast<LONG>(m_descBoxLeft + m_descBoxWidth);
        titleRect.top = static_cast<LONG>(m_bCY - m_bH * 0.5f);
        titleRect.bottom = static_cast<LONG>(m_descBoxTop - 5.f);

        DrawTextW(_hdc, title, -1, &titleRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
    }

    // 설명 박스
    if (!m_candidates.empty() && m_cursor >= 0 && m_cursor < (int)m_candidates.size()) {
        UnitData* currentUnit = m_candidates[m_cursor];
        if (currentUnit) {
            GDISelector fontSel(_hdc, FontType::PIXEL_BIG);
            SetBkMode(_hdc, TRANSPARENT);
            SetTextColor(_hdc, RGB(220, 220, 220));

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
            const int lineSpacing = 20;

            RECT tempRect = { 0, 0, static_cast<LONG>(m_descBoxWidth - padding * 2), 0 };
            LONG curY = static_cast<LONG>(m_descBoxTop + padding);

            for (const auto& line : lines) {
                RECT calc = tempRect;
                DrawTextW(_hdc, line.c_str(), -1, &calc, DT_LEFT | DT_TOP | DT_WORDBREAK | DT_NOPREFIX | DT_CALCRECT);
                LONG lineHeight = calc.bottom - calc.top;

                RECT lineRect;
                lineRect.left = static_cast<LONG>(m_descBoxLeft + padding);
                lineRect.right = static_cast<LONG>(m_descBoxLeft + m_descBoxWidth - padding);
                lineRect.top = curY;
                lineRect.bottom = curY + lineHeight;

                DrawTextW(_hdc, line.c_str(), -1, &lineRect, DT_LEFT | DT_TOP | DT_WORDBREAK | DT_NOPREFIX);

                curY += lineHeight + lineSpacing;
            }
        }
    }

    // 유닛 타일 렌더링
    int maxDraw = std::min<int>((int)m_candidates.size(), m_cols * m_rows);
    for (int i = 0; i < maxDraw; ++i) {
        int col = i % m_cols;
        int row = i / m_cols;

        float x = m_startX + col * (m_tileW + m_spacingX) + m_tileW * 0.5f;
        float y = m_startY + row * (m_tileH + m_spacingY) + m_tileH * 0.5f;

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
            ::TransparentBlt(
                _hdc,
                (int)(x - m_tileW * 0.5f),
                (int)(y - m_tileH * 0.5f),
                (int)m_tileW,
                (int)m_tileH,
                m_selectBoxTex->GetTextureDC(),
                0, 0, srcW, srcH,
                RGB(255, 0, 255));
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