#pragma once
#include "Stage.h"

class StageManager
{
	DECLARE_SINGLE(StageManager);
public:
	vector<vector<Stage*>> GenerateStageMap();
	bool IsReset() const { return m_isReset; }
	void SetReset() { m_isReset = true; }
	void Release();
private:
	StageType RandomStageType()
	{
		int random = rand() % 100;

		if (random < (int)StageType::TreatmentCenter) return StageType::TreatmentCenter;
		else if (random < (int)StageType::Exchange) return StageType::Exchange;
		else return StageType::Normal;
	}
private:
	const int StageLength = 10;
	const int MaxStageCount = 4;
	const int MinStageCount = 2;

	vector<vector<Stage*>> m_stages;
	bool m_isReset = true;
};

