#pragma once
#include "Object.h"
class ActionData;
class BattleDescription : public Object
{
public:
	void SetText(ActionData* _actionData);
	void Render(HDC _hdc) override;
private :
	wstring m_text;
};

