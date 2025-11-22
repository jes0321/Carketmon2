#pragma once
#include "Object.h"
class Texture;
class Projectile :
    public Object
{
public:
    Projectile();
    ~Projectile();
public:
    void Update() override;
    // Object을(를) 통해 상속됨
    void Render(HDC _hdc) override;
public:
    void SetAngle(float _angle) { m_angle = _angle; }
    void SetDir(Vec2 _dir)
    {
        m_dir = _dir;
        m_dir.Normalize();
    }
private:
    float m_angle;
    Vec2  m_dir;
    Texture* m_pTex;
};

