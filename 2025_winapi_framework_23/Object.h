#pragma once
class Component;
class Collider;
class Object
{
public:
	Object();
	virtual ~Object();
public:
	virtual void Update() abstract;
	virtual void LateUpdate();
	virtual void Render(HDC _hdc) abstract;
	void ComponentRender(HDC _hdc);
	virtual void EnterCollision(Collider* _other) {}
	virtual void StayCollision(Collider* _other) {}
	virtual void ExitCollision(Collider* _other) {}
public:
	// public 헬퍼
	void Translate(Vec2 _delta)
	{
		m_pos.x += _delta.x;
		m_pos.y += _delta.y;
	}
	void Scale(Vec2 _s)
	{
		if (_s.x <= 0.f || _s.y <= 0.f)
			return;
		m_size.x *= _s.x;
		m_size.y *= _s.y;
	}
public:
	void SetPos(Vec2 _pos) { m_pos = _pos; }
	void SetSize(Vec2 _size) { m_size = _size; }
	const Vec2& GetPos() const { return m_pos; }
	const Vec2& GetSize()const { return m_size; }
	bool GetIsDead() const { return m_isDie; }
	void SetDead() { m_isDie = true; }
public:
	template<typename T>
	T* AddComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "Component로부터 상속받아야 함");
		T* compo = new T;
		compo->SetOwner(this);
		compo->Init(); // 선택
		m_vecComponents.push_back(compo);
		return compo;
	}
	template<typename T>
	T* GetComponent()
	{
		T* compo = nullptr;
		for (Component* com : m_vecComponents)
		{
			compo = dynamic_cast<T*>(com);
			if (compo)
				break;
		}
		return compo;
	}
private:
	Vec2 m_pos;
	Vec2 m_size;
	vector<Component*> m_vecComponents;
	bool m_isDie;
};

