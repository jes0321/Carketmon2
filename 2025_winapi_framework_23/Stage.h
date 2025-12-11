#pragma once
#include "Object.h"
#include "UnitData.h"

enum StageType
{
	Normal,
	Exchange = 30, //치료센터
	TreatmentCenter = 15, //교환소
	Boss,
};

class Stage :
	public Object
{
public:
	Stage(int _stageNum, int _stageRowIndex, int _stageLengthIndex,
		StageType _stageType);
	~Stage();
public:
	void Render(HDC _hdc);
	void Update() override;
public:
	void AddNextStage(Stage* _stage) { m_nextStages.push_back(_stage); }
	void SetBeforeStage(Stage* _stage) { m_beforeStage = _stage; }

	void SetUnitData(UnitData* _unitData) { m_unitData = _unitData; }

	Stage* GetBeforeStage() const { return m_beforeStage; }
	vector<Stage*> GetNextStages() const { return m_nextStages; }

	UnitData* GetUnitData() const { return m_unitData; }
	StageType GetStageType() const { return m_stageType; }

	int GetStageNumber() const { return m_stageNumber; }
	int GetStageRowIndex() const { return m_stageRowIndex; }
	int GetStageLengthIndex() const { return m_stageLengthIndex; }
private:
	std::wstring StageTypeToString(StageType _stageType)
	{
		std::wstring wstr;
		std::string str;

		switch (_stageType)
		{
		case StageType::Normal:			str = "Normal";
			break;
		case StageType::Boss:			str = "Boss";
			break;
		case StageType::TreatmentCenter:str = "TreatmentCenter";
			break;
		case StageType::Exchange:		str = "Exchange";
			break;
		}

		wstr.assign(str.begin(), str.end());
		return wstr;
	}
public:
	bool IsAvailable = true;
	bool IsSeleted = false;
	bool IsCompelet = false;
private:
	vector<Stage*> m_nextStages;
	Stage* m_beforeStage = nullptr;
	UnitData* m_unitData;
	StageType m_stageType = StageType::Normal;
	int m_stageNumber = 0;
	int m_stageRowIndex = 0;
	int m_stageLengthIndex = 0;
};

