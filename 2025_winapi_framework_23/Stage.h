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
	void SettingStage(int _stageNum, int _stageRowIndex, int _stageLengthIndex)
	{
		m_stageNumber = _stageNum;
		m_stageRowIndex = _stageRowIndex;
		m_stageLengthIndex = _stageLengthIndex;
	}
	void AddNextStage(Stage* _stage) { m_nextStages.push_back(_stage); }
	void SettingBeforeStage(Stage* _stage) { m_beforeStage = _stage; }

	Stage* GetBeforeStage() { return m_beforeStage; }
	vector<Stage*> GetNextStages() { return m_nextStages; }

	int GetStageNumber() { return m_stageNumber; }
	int GetStageRowIndex() { return m_stageRowIndex; }
	int GetStageLengthIndex() { return m_stageLengthIndex; }
public:
	bool IsAvailable = true;
	bool IsSeleted = false;
	bool IsCompelet = false;
private:
	vector<Stage*> m_nextStages;
	Stage* m_beforeStage = nullptr;
	int m_stageNumber = 0;
	int m_stageRowIndex = 0;
	int m_stageLengthIndex = 0;
};

