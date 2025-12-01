#pragma once
#include "Object.h"
class Stage : 
	public Object
{
public:
	Stage();
	~Stage();
public:
	void Render(HDC _hdc);
	void Update() override;
	void AddNextStage(Stage* _stage) 
	{ 
		m_nextStages.push_back(_stage); 
	}
	void SettingBeforeStage(Stage* _stage)
	{
		m_beforeStage = _stage;
	}
	Stage* GetBeforeStage()
	{
		return m_beforeStage;
	}
	vector<Stage*> GetNextStages()
	{
		return m_nextStages;
	}
public:
	bool IsSeleted = false;
private:
	vector<Stage*> m_nextStages;
	Stage* m_beforeStage = nullptr;
};

