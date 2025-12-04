#pragma once
#include "Object.h"

enum StageType
{
	Normal = 0,
	TreatmentCenter = 25, //치료센터
	Exchange = 20, //교환소
	Max, //교환소
	
	Boss, 
};

class Stage :
	public Object
{
public:
	Stage();
	~Stage();
public:
	void Render(HDC _hdc);
	void Update() override;
	void SettingStage(int _stageNum, int _stageRowIndex, int _stageLengthIndex,
						StageType _stageType)
	{
		m_stageNumber = _stageNum;
		m_stageRowIndex = _stageRowIndex;
		m_stageLengthIndex = _stageLengthIndex;
		m_stageType = _stageType;
	}
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
	StageType m_stageType = StageType::Normal;
	int m_stageNumber = 0;
	int m_stageRowIndex = 0;
	int m_stageLengthIndex = 0;
};

