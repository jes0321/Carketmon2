#include "pch.h"
#include "SceneManager.h"
#include "Object.h"
#include "Collider.h"
#include "StageSelectScene.h"
#include "BattleScene.h"
#include "TitleScene.h"
#include "StartScene.h"
void SceneManager::PhysicsSyncColliders()
{
	for (UINT i = 0; i < (UINT)Layer::END; ++i)
	{
		const auto& objects = m_curScene->GetLayerObjects((Layer)i);
		for (Object* obj : objects)
		{
			if (!obj)
				continue;

			if (auto* col = obj->GetComponent<Collider>())
				col->LateUpdate(); // sync  
		}
	}
}
void SceneManager::Init()
{
	m_curScene = nullptr;
	RegisterScene(L"StageSelectScene", std::make_shared<StageSelectScene>());
	RegisterScene(L"BattleScene", std::make_shared<BattleScene>());
	RegisterScene(L"TitleScene", std::make_shared<TitleScene>());
	RegisterScene(L"StartScene", std::make_shared<StartScene>());
	LoadScene(L"TitleScene");
	// MenuScene 등록
}
void SceneManager::Update()
{
	if (m_curScene == nullptr)
		return;
	m_curScene->Update();
	m_curScene->LateUpdate();
}

void SceneManager::FixedUpdate(float _fixedDT)
{
	if (m_curScene == nullptr)
		return;
	m_curScene->FixedUpdate(_fixedDT);
	PhysicsSyncColliders();
}

void SceneManager::Render(HDC _hdc)
{
	if (m_curScene == nullptr)
		return;
	m_curScene->Render(_hdc);
}

BattleScene* SceneManager::GetBattleScene()
{
	if (m_curScene == nullptr)
		return nullptr;
	return dynamic_cast<BattleScene*>(m_curScene.get());
}

void SceneManager::RegisterScene(const wstring& _name, std::shared_ptr<Scene> _scene)
{
	if (_name.empty() || _scene == nullptr)
		return;
	m_mapScenes.insert(m_mapScenes.end(), { _name, _scene });
}

void SceneManager::LoadScene(const wstring& _name)
{
	// 2��° load �Ͻ� change ����
	if (m_curScene != nullptr)
	{
		m_curScene->Release();
		m_curScene = nullptr;
	}
	auto iter = m_mapScenes.find(_name);
	if (iter != m_mapScenes.end())
	{
		m_curScene = iter->second;
		m_curScene->Init();
	}
}
