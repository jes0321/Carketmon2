#pragma once
#include "Object.h"
class Enemy : public Object
{
public:
    Enemy();
    ~Enemy();
public:
    void Update() override;
    // Object을(를) 통해 상속됨
    void Render(HDC _hdc) override;
public:
    void EnterCollision(Collider* _other) override;
    void StayCollision(Collider* _other) override;
    void ExitCollision(Collider* _other) override;
};

