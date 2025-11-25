#pragma once
#include "Stage.h"
class StageSpawner
{
public:
	StageSpawner();
	~StageSpawner();
public:
	void SpawnStage();
	void ChangeStage(int _stageIndex)
	{
		if(_stageIndex > 4 || _stageIndex < 0)
			return;
	};
	void SetCurrentStageIndex(int _currentStageIndex) { m_currentStageIndex = _currentStageIndex; }
	void SetStageXLength(int _stageXLength) { m_stageXLength = _stageXLength; }
	void SetStageYLength(int _stageYLength) { m_stageYLength = _stageYLength; }
	const int GetCurrentStageIndex() const { return m_currentStageIndex; }
	const int GetStageXLength() const { return m_stageXLength; }
	const int GetStageYLength() const { return m_stageYLength; }
private:
	Stage* _stages[5];
	float m_stageXLength = 1;
	float m_stageYLength = 1;
	int m_currentStageIndex = 0;
};

