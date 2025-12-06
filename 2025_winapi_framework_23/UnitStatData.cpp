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

	if(m_upgradeStats[index]<0)
		return m_stat[index] * (2/ (2 + std::abs(m_upgradeStats[index])));
	return m_stat[index] * ((2+m_upgradeStats[index])/2);
}

void UnitStatData::UpgradeStat(StatType _type, int amount)
{
	int index = static_cast<int>(_type);
	m_upgradeStats[index] += amount;
	if(m_upgradeStats[index] < -6)
		m_upgradeStats[index] = -6;
	else if(m_upgradeStats[index]>6)
		m_upgradeStats[index] = 6;
}
