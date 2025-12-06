#pragma once
#include "Stage.h"

class StageManager
{
	DECLARE_SINGLE(StageManager);
public:
	void SetCurrentStage(Stage* _stage) { m_currentStage = _stage; }
	Stage* GetCurrentStage() const { return m_currentStage; }
private:
	Stage* m_currentStage;
};

