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
#include <fstream>
#include <sstream>
#include <algorithm>

void StartScene::Init()
{
    m_selectVec.clear();
    m_candidates.clear();

    LoadUnitsFromTxt(L"Texture\\UnitList.txt");

    m_btnManager = new ButtonSwitcher;
    m_btnManager->OnOffInput(false);
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
            obj->SetOnClick([this]() {
                CancelSelectAll();
                }, "취소");
        }
        break;
        case 1:
        {
            obj->SetOnClick([this]() {
                // 선택 2개 검증
                if (m_selectVec.size() < 2 || !m_selectVec[0] || !m_selectVec[1]) {
                    SetSelectionEnabled(true);
                    m_btnManager->OnOffInput(false);
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

void StartScene::LoadUnitsFromTxt(const std::wstring& relativeTxtPath)
{
    wchar_t buf[MAX_PATH] = {};
    ::GetModuleFileNameW(nullptr, buf, MAX_PATH);
    fs::path exeDir = fs::path(buf).parent_path();
    fs::path resourceDir = exeDir.parent_path() / L"build" / L"Resource\\";
    fs::path txtPath = resourceDir / relativeTxtPath;

    std::ifstream fin(txtPath.string(), std::ios::binary);
    if (!fin.is_open()) return;

    std::string line;
    char bom[3] = {};
    fin.read(bom, 3);
    if (!(bom[0] == char(0xEF) && bom[1] == char(0xBB) && bom[2] == char(0xBF))) {
        fin.seekg(0);
    }
    std::getline(fin, line);
    fin.close();

    int wlen = ::MultiByteToWideChar(CP_UTF8, 0, line.c_str(), (int)line.size(), nullptr, 0);
    if (wlen <= 0) return;
    std::wstring content;
    content.resize(wlen);
    ::MultiByteToWideChar(CP_UTF8, 0, line.c_str(), (int)line.size(), &content[0], wlen);

    std::wstringstream ss(content);
    std::wstring name;
    while (std::getline(ss, name, L','))
    {
        name.erase(0, name.find_first_not_of(L" \t\r\n"));
        if (!name.empty()) name.erase(name.find_last_not_of(L" \t\r\n") + 1);
        if (name.empty()) continue;

        UnitData* data = GET_SINGLE(UnitManager)->GetUnit(name);
        if (data) m_candidates.push_back(data);
    }
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

    {
        const float padX = 20.f;
        const float padY = 20.f;
        const float bW = gridWidth + padX * 2.f;
        const float bH = gridHeight + padY * 2.f;
        const float bCX = startX + gridWidth * 0.5f;
        const float bCY = startY + gridHeight * 0.5f;

        GDISelector penSel(_hdc, PenType::BOLD_GREEN);
        GDISelector brushSel(_hdc, BrushType::HOLLOW);
        RECT_RENDER(_hdc, bCX, bCY, bW, bH);
    }

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
    m_btnManager->OnOffInput(!enabled);
}