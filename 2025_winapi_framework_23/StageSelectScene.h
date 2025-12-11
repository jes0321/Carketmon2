#pragma once
#include "Scene.h"
#include "Stage.h"
#include "StageManager.h"

class Image;
class StageSelectScene : public Scene
{
public:
	~StageSelectScene() override;
public:
	// Scene��(��) ���� ��ӵ�
	void Init() override;
	void Update() override;
	void Render(HDC _hdc) override;
	void Release() override;
public:
	Stage* GetCurrentStage() const { return m_currentStage; }
private:
	void StageDebugLog();
private:
	StageType RandomStageType()
	{
		int random = rand() % 100;

		if (random < (int)StageType::TreatmentCenter) return StageType::TreatmentCenter;
		else if (random < (int)StageType::Exchange) return StageType::Exchange;
		else return StageType::Normal;
	}
	void MoveStage();
	void SetCurrentStage(Stage* _stages)
	{
		if (m_currentStage != nullptr)
			m_currentStage->IsSeleted = false;

		m_currentStage = _stages;
		m_currentStage->IsSeleted = true;

	}
	bool ChangeStage(int _stageIndex)
	{
		if (_stageIndex > StageLength - 1)
		{
			m_currentStageLength = StageLength - 1;
			return false;
		}
		if (_stageIndex < 0)
		{
			m_currentStageLength = 0;
			return false;
		}

		return true;
	}
private:
	const int StageLength = 10;
	const int MaxStageCount = 4;
	const int MinStageCount = 2;
private:
	Image* m_bgImage = nullptr;
	Vec2 m_prevBgPos = {WINDOW_WIDTH / 2, 0};  // 이전 배경 위치 추가
	vector<vector<Stage*>> m_stages;
	Stage* m_currentStage = nullptr;
	int m_currentStageLength = 0;
	int m_currentSelectStageLength = 0;
	int m_currentStageIndex = 0;
	int m_LifeCount = 0;
};

