#include "pch.h"
#include "Scene.h"
#include "Object.h"
#include "CollisionManager.h"
#include "Rigidbody.h"
#include "Object.h"
Scene::Scene()
{
}

Scene::~Scene()
{
	Release();
}

void Scene::Update()
{
	// obj update
	for (UINT i = 0; i < (UINT)Layer::END; ++i)
	{
		auto& vec = m_vecObj[i];
		for (auto* obj : vec)
			if(!obj->GetIsDead())
				obj->Update();
	}
}

void Scene::LateUpdate()
{
	for (UINT i = 0; i < (UINT)Layer::END; ++i)
	{
		auto& vec = m_vecObj[i];
		for (auto* obj : vec)
			if (!obj->GetIsDead())
				obj->LateUpdate();
	}
}

void Scene::FixedUpdate(float _fixedDT)
{
	for (UINT i = 0; i < (UINT)Layer::END; ++i)
	{
		auto& vec = m_vecObj[i];
		for (auto* obj : vec)
		{
			if (auto rb = obj->GetComponent<Rigidbody>())
			{
				if (rb != nullptr)
					rb->FixedUpdate(_fixedDT);
			}
		}
	}
}

void Scene::Render(HDC _hdc)
{
	// obj render
	for (UINT i = 0; i < (UINT)Layer::END; ++i)
	{
		auto& vec = m_vecObj[i];
		for (auto* obj : vec)
			if (!obj->GetIsDead())
				obj->Render(_hdc);
	}
}


void Scene::Release()
{
	FlushEvent();
	for (UINT i = 0; i < (UINT)Layer::END; ++i)
	{
		auto& vec = m_vecObj[i];
		for (auto* obj : vec)
			SAFE_DELETE(obj);
		vec.clear();
	}
	GET_SINGLE(CollisionManager)->CheckReset();
}

void Scene::FlushEvent()
{
	// 삭제
	for (Object* obj : m_killObject)
	{
		if (obj != nullptr)
		{
			RemoveObject(obj);
			SAFE_DELETE(obj);
		}
	}
	m_killObject.clear();

	// 생성
}

void Scene::RequestDestroy(Object* obj)
{
	if (obj == nullptr)
		return;
	if (!obj->GetIsDead())
	{
		obj->SetDead();
		m_killObject.push_back(obj);
	}
}

void Scene::RemoveObject(Object* _obj)
{
	for (UINT i = 0; i < (UINT)Layer::END; ++i)
	{
		auto& v = m_vecObj[i];
		v.erase(std::remove(v.begin(), v.end(), _obj), v.end());
	}
}


void Scene::RequestSpawn(Object* obj, Layer _type)
{

}


