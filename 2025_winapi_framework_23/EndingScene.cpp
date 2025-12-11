#include "pch.h"
#include "EndingScene.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "InputManager.h"

void EndingScene::Init()
{
    m_credit = L"보스를 잡으셨습니다!\n정말 축하드립니다.\n게임을 여기까지 플레이 해주셔서 감사합니다.\n\n제작\n\n팀장 : 정은성\n팀원 : 김우진\n아트 : 김우진\n가장 열심히 한 사람 : 김우진";

    // 크레딧을 라인별로 분리
    m_creditLines.clear();
    size_t start = 0;
    while (true) {
        size_t pos = m_credit.find(L'\n', start);
        if (pos == std::wstring::npos) {
            m_creditLines.push_back(m_credit.substr(start));
            break;
        }
        m_creditLines.push_back(m_credit.substr(start, pos - start));
        start = pos + 1;
    }

    // 화면 하단에서 시작
    m_currentOffset = (float)WINDOW_HEIGHT;
}

void EndingScene::Update()
{
    Scene::Update();
    if (m_isScrolling == false) {
        if(GET_KEYUP(KEY_TYPE::ENTER))
			GET_SINGLE(SceneManager)->LoadScene(L"TitleScene");

		return;
    }
    // 일정한 속도로 스크롤
    m_currentOffset -= m_scrollSpeed * fDT;

    // 전체 크레딧 높이 계산
    float totalHeight = m_creditLines.size() * m_lineSpacing;

    // 크레딧이 완전히 끝나면 위치 고정
    if (m_currentOffset < -totalHeight) {
        m_currentOffset = -totalHeight;
		m_isScrolling = false;
    }
}

void EndingScene::Render(HDC _hdc)
{
    // 배경을 어둡게
    {
        HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
        HBRUSH hOldBrush = (HBRUSH)SelectObject(_hdc, hBrush);
        Rectangle(_hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        SelectObject(_hdc, hOldBrush);
        DeleteObject(hBrush);
    }

    Scene::Render(_hdc);


    // 폰트 및 텍스트 색상 설정
    GDISelector fontSel(_hdc, FontType::PIXEL_BIG);
    SetBkMode(_hdc, TRANSPARENT);
    SetTextColor(_hdc, RGB(255, 255, 255));

    if (m_isScrolling == false) {
        const wchar_t* message = L"엔터를 눌러 타이틀로 가기";
        RECT textRect;
        textRect.left = 0;
        textRect.right = WINDOW_WIDTH;
        textRect.top = WINDOW_HEIGHT / 2 - 50;
        textRect.bottom = WINDOW_HEIGHT / 2 + 50;

        DrawTextW(_hdc, message, -1, &textRect,
            DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
        return;
    }

    // 크레딧 라인 렌더링
    float currentY = m_currentOffset;

    for (const auto& line : m_creditLines) {
        // 화면 내 또는 근처에 있는 라인만 렌더링
        if (currentY > -m_lineSpacing && currentY < WINDOW_HEIGHT + m_lineSpacing) {
            RECT textRect;
            textRect.left = 0;
            textRect.right = WINDOW_WIDTH;
            textRect.top = (LONG)currentY;
            textRect.bottom = (LONG)(currentY + m_lineSpacing);

            DrawTextW(_hdc, line.c_str(), -1, &textRect,
                DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
        }

        currentY += m_lineSpacing;
    }
}