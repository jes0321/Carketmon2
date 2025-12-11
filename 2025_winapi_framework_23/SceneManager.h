#pragma once
//class Scene;
#include "Scene.h"
class BattleScene;
class SceneManager
{
	DECLARE_SINGLE(SceneManager);
public:
	void Init();
	void Update(); // LateUpdate;
	void FixedUpdate(float _fixedDT);
	void Render(HDC _hdc);	
	void Release();
public:
	void RequestDestroy(Object* obj)
	{
		if (m_curScene)
			m_curScene->RequestDestroy(obj);
	}
public:
	BattleScene* GetBattleScene();
	void RegisterScene(const wstring& _name, Scene* _scene);
	void LoadScene(const wstring& _name);
private:
	void ChangeScene();
public:
	Scene* GetCurScene() const
	{
		return m_curScene;
	}
private:
	float m_timer = 0;
	float m_delayTime = 0.05f;
	bool m_isTras = false;
	wstring m_nextSceneName;
	Scene* m_curScene;
	std::unordered_map<wstring, Scene*> m_mapScenes;
};
