#pragma once
#include "Component.h"
class Collider :   public Component
{
public:
    Collider();
    ~Collider();
public:
	// Component을(를) 통해 상속됨
	void Init() override;
	void LateUpdate() override;
	void Render(HDC _hdc) override;
public:
    void SetSize(Vec2 _size) { m_size = _size; }
    const Vec2& GetSize() const { return m_size; }
    void SetOffSetPos(Vec2 _OffsetPos)
    {
        m_offsetPos = _OffsetPos;
    }
    const Vec2& GetOffSetPos() const { return m_offsetPos; }
    const Vec2& GetUpdatedPos() const
    {
        return m_updatedPos;
    }
    UINT GetID() const { return m_ID; }
    void EnterCollision(Collider* _other);
    void StayCollision(Collider* _other);
    void ExitCollision(Collider* _other);
    void SetName(const wstring& n) { m_name = n; }
    const wstring& GetName() const { return m_name; }

    void SetTrigger(bool t) { m_isTrigger = t; }
    bool IsTrigger() const { return m_isTrigger; }
private:
    Vec2 m_size; // 콜라이더 크기
    // Object로부터 상대적인 위치
    Vec2 m_offsetPos;
    // LateUpdate에서 매 프레임마다 오브젝트로부터 계산되는 위치
    Vec2 m_updatedPos;
    UINT m_ID; // 충돌체 고유 ID값
    static UINT m_nextID;
    bool m_showDebug;
    wstring m_name;
    bool m_isTrigger;
};

