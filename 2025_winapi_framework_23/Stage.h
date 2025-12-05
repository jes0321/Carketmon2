#pragma once
#include "Object.h"
#include "UnitData.h"

enum StageType
{
	Normal = 0,
	TreatmentCenter = 25, //치료센터
	Exchange = 20, //교환소
	Max, 
	
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
	void AddNextStage(Stage* _stage) { m_nextStages.push_back(_stage); }
	void SettingBeforeStage(Stage* _stage) { m_beforeStage = _stage; }

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
		default:						str = "UNKNOWN";
		}

		wstr.assign(str.begin(), str.end());
		return wstr;
	}

	Stage* GetBeforeStage() const { return m_beforeStage; }
	vector<Stage*> GetNextStages() const { return m_nextStages; }

	int GetStageNumber() const { return m_stageNumber; }
	int GetStageRowIndex() const { return m_stageRowIndex; }
	int GetStageLengthIndex() const { return m_stageLengthIndex; }
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

