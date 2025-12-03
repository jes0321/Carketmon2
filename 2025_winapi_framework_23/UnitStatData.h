#pragma once
class UnitStatData
{
public:
	UnitStatData(int attack, int defense, int speed);
	int GetStat(StatType _type) const;
	void UpgradeStat(StatType _type, int amount);
private:
	int m_upgradeStats[3];
	int m_stat[3];
};

