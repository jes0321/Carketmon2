#include "pch.h"
#include "UnitStatData.h"

UnitStatData::UnitStatData(int attack, int defense, int speed)
{
	m_stat[static_cast<int>(StatType::Attack)] = attack;
	m_stat[static_cast<int>(StatType::Defense)] = defense;
	m_stat[static_cast<int>(StatType::Speed)] = speed;

	for(int i=0;i<3;++i)
	{
		m_upgradeStats[i] = 0;
	}
}

int UnitStatData::GetStat(StatType _type) const
{
	int index = static_cast<int>(_type);
	return m_stat[index] + m_upgradeStats[index];
}

void UnitStatData::UpgradeStat(StatType _type, int amount)
{
	m_upgradeStats[static_cast<int>(_type)] += amount;
}
