#pragma once
class UnitStatData
{
public:
	UnitStatData(int attack, int defense, int speed);
	int GetStat(StatType _type) const;
	int GetOriginalStat(StatType _type) const { return m_stat[static_cast<int>(_type)]; }
	int GetUpgradeCost(int idx) const { return m_upgradeStats[idx]; }
	void UpgradeStat(StatType _type, int amount);
private:
	int m_upgradeStats[3];
	int m_stat[3];
};

