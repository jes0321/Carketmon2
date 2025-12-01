#include "pch.h"
#include "Scene.h"
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
		for (auto* obj : vec) {
			if (obj->IsActive())
				obj->Update();
		}
	}
}

void Scene::LateUpdate()
{
	for (UINT i = 0; i < (UINT)Layer::END; ++i)
	{
		auto& vec = m_vecObj[i];
		for (auto* obj : vec) {
			if (obj->IsActive())
				obj->LateUpdate();
		}
	}
}

void Scene::FixedUpdate(float _fixedDT)
{
	for (UINT i = 0; i < (UINT)Layer::END; ++i)
	{
		auto& vec = m_vecObj[i];
	}
}

void Scene::Render(HDC _hdc)
{
	// obj render
	for (UINT i = 0; i < (UINT)Layer::END; ++i)
	{
		auto& vec = m_vecObj[i];
		for (auto* obj : vec) {
			if (obj->IsActive())
				obj->Render(_hdc);
		}
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
}

void Scene::FlushEvent()
{
	// ����

	// ����
}

void Scene::RequestDestroy(Object* obj)
{
	if (obj == nullptr)
		return;
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


