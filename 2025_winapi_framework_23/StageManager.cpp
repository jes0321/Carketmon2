#include "pch.h"
#include "StageManager.h"

vector<vector<Stage*>>  StageManager::GenerateStageMap()
{
	m_isReset = false;
	int stageNumber = 1;
	Release();
	for (int i = 0; i < StageLength; i++)
	{
		int stageCount = rand() % MaxStageCount + MinStageCount;

		// 첫 스테이지와 마지막 스테이지 1개로 고정
		if (i == StageLength - 1 || i == 0)
			stageCount = 2;

		vector<Stage*> stageRow;

		for (int j = 1; j < stageCount; j++)
		{
			int posX = (WINDOW_WIDTH / stageCount + 1) * j;

			//StageType randStageType = (StageType)(rand() % StageType::Max);
			StageType randStageType = RandomStageType();

			if (i == StageLength - 1)
				randStageType = StageType::Boss;
			else if (i == 0)
				randStageType = StageType::Normal;

			Stage* obj = new Stage(stageNumber, j - 1, i, randStageType);
			obj->SetPos({ posX , (-120 * i) + 300 });
			obj->SetSize({ 100,100 });
			//AddObject(obj, Layer::DEFAULT);
			stageRow.push_back(obj);

			++stageNumber;

			if (i == 0) break;

			Stage* before = m_stages[i - 1][rand() % m_stages[i - 1].size()];
			obj->SetBeforeStage(before);
			before->AddNextStage(obj);

		}

		//만약 이전 스테이지에서 다음 스테이지가 
		// 설정되지 못한 스테이지가 존재한다면 연결
		if (i > 0)
		{
			for (Stage* prev : m_stages[i - 1])
			{
				if (prev->GetNextStages().empty())
				{
					Stage* randomNext = stageRow[rand() % stageRow.size()];
					prev->AddNextStage(randomNext);
				}
			}
		}

		m_stages.push_back(stageRow);
	}
	return m_stages;
}
void StageManager::Release() {
	for (auto& stageRow : m_stages)
	{
		for (Stage* stage : stageRow)
		{
			SAFE_DELETE(stage);
		}
		stageRow.clear();
	}
	m_stages.clear();
}
