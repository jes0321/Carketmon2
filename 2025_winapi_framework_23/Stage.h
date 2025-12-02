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
	void SettingStage(int _stageIndex, int _stageNum)
	{
		m_stageNumber = _stageNum;
		m_stageIndex = _stageIndex;
	}
	void AddNextStage(Stage* _stage) 
	{ 
		m_nextStages.push_back(_stage); 
	}
	void SettingBeforeStage(Stage* _stage)
	{
		m_beforeStage = _stage;
	}
	Stage* GetBeforeStage() { return m_beforeStage; }
	vector<Stage*> GetNextStages() { return m_nextStages; }
	int GetStageNumber() { return m_stageNumber; }
	int GetStageIndex() { return m_stageIndex; }
public:
	bool IsSeleted = false;
private:
	vector<Stage*> m_nextStages;
	Stage* m_beforeStage = nullptr;
	int m_stageNumber = 0;
	int m_stageIndex = 0;
};

