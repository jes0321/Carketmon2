#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Stage.h"
#include "UnitManager.h"

Stage::Stage(int _stageNum, int _stageRowIndex, int _stageLengthIndex,
		StageType _stageType)
{
	m_stageNumber = _stageNum;
	m_stageRowIndex = _stageRowIndex;
	m_stageLengthIndex = _stageLengthIndex;
	m_stageType = _stageType;

	m_unitData = GET_SINGLE(UnitManager)->UnitManager::GetUnitRandom();
}

Stage::~Stage()
{
}

void Stage::Update()
{
	if (m_stageType != StageType::Normal || m_unitData == nullptr)
		m_unitData = GET_SINGLE(UnitManager)->UnitManager::GetUnitRandom();
}

void Stage::Render(HDC _hdc)
{
	COLORREF color;

	if (IsAvailable)
		color = IsSeleted ? RGB(100, 100, 100) : RGB(255, 255, 255);
	else
	{
		color = IsCompelet ? RGB(255, 255, 0) : RGB(255, 0, 255);
	}

	HBRUSH hbrush = ::CreateSolidBrush(color);
	HBRUSH holdbrush = (HBRUSH)::SelectObject(_hdc, hbrush);

	Vec2 pos = GetPos();
	Vec2 size = GetSize();

	if (m_nextStages.empty() == false)
	{
		for (int i = 0; i < m_nextStages.size(); i++)
		{
			::MoveToEx(_hdc, pos.x, pos.y, nullptr);

			Vec2 nextPos = m_nextStages[i]->GetPos();
			::LineTo(_hdc, nextPos.x, nextPos.y);
		}
	}

	RECT_RENDER(_hdc, pos.x, pos.y, size.x, size.y);

	RECT rc;
	//static_cast 안전한 변환만 허용, 위험한 변환은 컴파일러가 막아줌
	rc.left = static_cast<LONG>(pos.x);
	rc.top = static_cast<LONG>(pos.y);
	rc.right = static_cast<LONG>(pos.x + size.x);
	rc.bottom = static_cast<LONG>(pos.y + size.y);

	//std::wstring text = std::to_wstring(m_stageNumber);
	std::wstring text2 = StageTypeToString(m_stageType);

	::SetTextColor(_hdc, IsSeleted ? RGB(255, 255, 255) : RGB(0, 0, 0));
	::SetBkMode(_hdc, TRANSPARENT);

	::DrawTextW(_hdc, text2.c_str(), -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	::SelectObject(_hdc, holdbrush);
	::DeleteObject(hbrush);

	if (m_stageType != StageType::Normal || m_unitData == nullptr) return;

	ElementType elementType = m_unitData->GetElementType();
	std::wstring _texName;

	switch (elementType)
	{
	case ElementType::Fire :
		_texName = L"Mark_Fire";
		break;
	case ElementType::Water:
		_texName = L"Mark_Water";
		break;
	case ElementType::Ice:
		_texName = L"Mark_Ice";
		break;
	case ElementType::Grace:
		_texName = L"Mark_Leaf";
		break;
	}

	Texture* tex =  GET_SINGLE(ResourceManager)->GetTexture(_texName);
	tex = m_unitData->GetTexture();
	LONG width = tex->GetWidth();
	LONG height = tex->GetHeight();

	::TransparentBlt(_hdc
		, (int)(pos.x - size.x / 2)
		, (int)(pos.y - size.y / 2)
		, (int)size.x
		, (int)size.y
		, tex->GetTextureDC()
		, 0, 0, width, height, RGB(255, 0, 255));
}
