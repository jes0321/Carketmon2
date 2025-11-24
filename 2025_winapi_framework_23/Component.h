#pragma once
class Object;
class Component
{
public:
	Component();
	virtual ~Component();
public:
	virtual void Init() =0;
	virtual void LateUpdate() = 0;
	virtual void Render(HDC _hdc) = 0;
public:
	void SetOwner(Object* _owner)
	{
		m_owner = _owner;
	}
	Object* GetOwner() const { return m_owner; }
private:
	Object* m_owner;
};

