#include "pch.h"
#include "ActionData.h"

void ActionData::UseCard()
{
	m_ownerUnit->UseCard(m_cardIdx);
}
