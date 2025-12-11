#include "pch.h"
#include "SceneManager.h"
#include "Object.h"
#include "Collider.h"
#include "StageSelectScene.h"
#include "ExchangeScene.h"
#include "TreatmentCenterScene.h"
#include "BattleScene.h"
#include "TitleScene.h"
#include "BattleEndScene.h"
#include "StartScene.h"
#include "EndingScene.h"
void SceneManager::Init()
{
	m_curScene = nullptr;
	RegisterScene(L"StageSelectScene", new StageSelectScene);
	RegisterScene(L"TreatmentCenterScene", new TreatmentCenterScene);
	RegisterScene(L"ExchangeScene", new ExchangeScene);
	RegisterScene(L"BattleScene", new BattleScene);
	RegisterScene(L"BattleEndScene", new BattleEndScene);
	RegisterScene(L"EndingScene", new EndingScene);
	RegisterScene(L"TitleScene", new TitleScene);
	RegisterScene(L"StartScene", new StartScene);
	LoadScene(L"TitleScene");
}
void SceneManager::Update()
{
	if (m_isTras) {
		m_timer += fDT;
		if (m_timer >= m_delayTime)
		{
			m_isTras = false;
			m_timer = 0;
			ChangeScene();
		}
		return;
	}
	if (m_curScene == nullptr)
		return;
	m_curScene->Update();
	m_curScene->LateUpdate();
}
void SceneManager::Release()
{
	for (auto& pair : m_mapScenes)
	{
		if (pair.second)
		{
			SAFE_DELETE(pair.second);
		}
	}
	m_mapScenes.clear();
	m_curScene = nullptr;
}
void SceneManager::FixedUpdate(float _fixedDT)
{
	if (m_curScene == nullptr)
		return;
	m_curScene->FixedUpdate(_fixedDT);
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
	return dynamic_cast<BattleScene*>(m_curScene);
}

void SceneManager::RegisterScene(const wstring& _name, Scene* _scene)
{
	if (_name.empty() || _scene == nullptr)
		return;
	m_mapScenes.insert(m_mapScenes.end(), { _name, _scene });
}

void SceneManager::LoadScene(const wstring& _name)
{
	m_isTras = true;
	m_nextSceneName = _name;
}

void SceneManager::ChangeScene()
{
	if (m_curScene != nullptr)
	{
		m_curScene->Release();
		m_curScene = nullptr;
	}
	auto iter = m_mapScenes.find(m_nextSceneName);
	if (iter != m_mapScenes.end())
	{
		m_curScene = iter->second;
		m_curScene->Init();
	}
}