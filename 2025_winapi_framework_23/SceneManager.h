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
public:
	Scene* GetCurScene() const
	{
		return m_curScene;
	}
private:
	// Scene* m_scene;
	Scene* m_curScene;
	std::unordered_map<wstring, Scene*> m_mapScenes;
};
