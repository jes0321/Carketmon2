#include "pch.h"
#include "Core.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
bool Core::Init(HWND _hWnd)
{
    m_hWnd = _hWnd;
    m_hDC = ::GetDC(m_hWnd);
    /*m_obj.SetPos({WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2});
    m_obj.SetSize({ 100,100 });*/
    
    m_hBackBit = 0;
    m_hBackDC = 0;

    // 더블버퍼링
    // 1. 필요한 작업 세팅
    // 도화지를 만드는거고
    m_hBackBit = ::CreateCompatibleBitmap(m_hDC, WINDOW_WIDTH, WINDOW_HEIGHT);

    // 호환되는 DC를 만들어주세요
    m_hBackDC = ::CreateCompatibleDC(m_hDC);

    // 2. 연결
    ::SelectObject(m_hBackDC, m_hBackBit);

    // == Manager == 

    GET_SINGLE(TimeManager)->Init();
    GET_SINGLE(InputManager)->Init();
    if (!GET_SINGLE(ResourceManager)->Init())
        return false;
    GET_SINGLE(SceneManager)->Init();
    return true;
}

void Core::CleanUp()
{
    ::DeleteDC(m_hBackDC);
    ::DeleteObject(m_hBackBit);
    ::ReleaseDC(m_hWnd, m_hDC);
    GET_SINGLE(ResourceManager)->Release();
}


void Core::MainUpdate()
{
    // == Manager == 
    GET_SINGLE(TimeManager)->Update();
    {
        static float accmulator = 0.f;
        const float fixedDT = 1.f / 60.f;
        accmulator += fDT;
        while (accmulator >= fixedDT)
        {
            GET_SINGLE(SceneManager)->FixedUpdate(fixedDT);
            GET_SINGLE(CollisionManager)->Update();
            accmulator -= fixedDT;
        }
    }
    GET_SINGLE(InputManager)->Update();
    GET_SINGLE(ResourceManager)->FmodUpdate();
    GET_SINGLE(SceneManager)->Update();
    //GET_SINGLE(CollisionManager)->Update();

    //Vec2 pos = m_obj.GetPos();
    ////if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    ////if(GET_SINGLE(InputManager)->IsPress(KEY_TYPE::LEFT))
    //  if(GET_KEY(KEY_TYPE::LEFT))
    //    pos.x -= 300.f * fDT;
    ////if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    ////if (GET_SINGLE(InputManager)->IsUp(KEY_TYPE::RIGHT))
    //  if(GET_KEYUP(KEY_TYPE::RIGHT))
    //      pos.x += 300.f *fDT;
    //  if(GET_KEYWIDTH(KEY_TYPE::CTRL, KEY_TYPE::SPACE))
    //      pos.y += 300.f *fDT;
    // 
    //m_obj.SetPos(pos);
}
void Core::MainRender()
{
    //::Rectangle(m_hBackDC, -1, -1, WINDOW_WIDTH +1, WINDOW_HEIGHT + 1);
    
    // clear
    ::PatBlt(m_hBackDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, WHITENESS);
    
    // render or draw
    GET_SINGLE(SceneManager)->Render(m_hBackDC);
    //Vec2 pos = m_obj.GetPos();
    //Vec2 size = m_obj.GetSize();
    //RECT_RENDER(m_hBackDC, pos.x, pos.y
    //                 , size.x, size.y);
    
    // display
    ::BitBlt(m_hDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, m_hBackDC, 0, 0, SRCCOPY);
}

void Core::GameLoop()
{
    //time(NULL);
    //FrameSync();
    //// ms
    //clock();

    //static int cnt = 0;
    //++cnt;
    //static int prev = GetTickCount64();
    //int cur = GetTickCount64();
    //if (cur - prev >= 1000)
    //{
    //    prev = cur;
    //    cnt = 0;
    //}


    MainUpdate();
    MainRender();
    GET_SINGLE(SceneManager)->GetCurScene()->FlushEvent();
}

