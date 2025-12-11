#include "pch.h"
#include "Texture.h"
#include "UnitData.h"
#include "UnitObject.h"
#include "SceneManager.h"
#include "DamageFloat.h"
#include "UnitStatData.h"
#include "ResourceManager.h"
#include "HealthBar.h"

void UnitObject::SetUnitData(UnitData* _data, int stage)
{
	m_unitData = _data;
	m_maxHp = m_unitData->GetMaxHp();
	m_currentHp = m_maxHp;
	for (int i = 0; i < 4; ++i) {
		CardData* card = m_unitData->GetCardRandom();
		m_handCards.push_back(card);
	}

	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	// 헬스바 사이즈 전반적으로 확대 (폭 100%, 높이 18)
	InitStats(stage);
	InitHealthBar(pos, size);
}

void UnitObject::InitHealthBar(const Vec2& pos, const Vec2& size)
{
	float barW = size.x * 1.0f;
	float barH = 18.f;

	// 유닛보다 조금 더 아래로 내리기 (기존 +6 에서 +12로)
	float barY = pos.y + size.y * 0.5f + 12.f;

	if (m_healthBar)
		SAFE_DELETE(m_healthBar);
	m_healthBar = new HealthBar(barW, barH);
	m_healthBar->SetPos({ pos.x, barY });
	m_healthBar->SetSize({ barW, barH });
	m_healthBar->SetValue(m_currentHp, m_maxHp);
}

void UnitObject::InitStats(int stage)
{
	if (m_statData)
		SAFE_DELETE(m_statData);

	int def = m_unitData->GetDef();
	int atk = m_unitData->GetAtk();
	int spd = m_unitData->GetSpeed();

	// 적 유닛인 경우 (stage >= 0) 스탯 강화
	if (stage > 0) {
		// HP 기본 1.8배 + 스테이지당 추가 증가 (최대 12스테이지 기준 약 0.36배 추가)
		// 1스테이지: 1.8배, 12스테이지: 약 2.16배
		float hpMultiplier = 1.8f + (stage * 0.03f); // 스테이지당 3% 추가 증가
		m_maxHp = (int)(m_maxHp * hpMultiplier);
		
		m_currentHp = m_maxHp;


		atk = (int)(atk * (1.1f + stage * 0.01f)); // 스테이지당 1% 증가
		def = (int)(def * (1.25f + stage * 0.01f)); // 스테이지당 1% 증가
		spd = (int)(spd * (1.05f + stage * 0.01f)); // 스테이지당 1% 증가
	}

	m_statData = new UnitStatData(
		atk,
		def,
		spd
	);
}

void UnitObject::SetBuffStat(StatType _type, int _value)
{
	m_statData->UpgradeStat(_type, _value);
}

void UnitObject::UseCard(int index)
{
	if (index < 0 || index >= (int)m_handCards.size())
		return;

	CardData* next = m_unitData->GetCardRandom();
	if (next) m_handCards.push_back(next);
	m_unitData->UseCard(index);
	m_handCards.erase(m_handCards.begin() + index);
}

bool UnitObject::Damage(int dmg, ElementType _type, bool _isPowerup)
{
	int Dmg = dmg - (m_statData->GetStat(StatType::Defense) * 0.4f);
	if (IsStrongAgainst(_type)) {
		GET_SINGLE(ResourceManager)->Play(L"Critical");
		Dmg *= 2;
	}
	else if (IsWeakAgainst(_type)) { Dmg *= 0.5f; }
	if (_isPowerup) { Dmg *= 1.5f; }
	if (m_isSheilded) { Dmg = 0; }
	else {
		// fDT 기반 블링크 트리거
		m_isBlinking = true;
		m_isBlinkVisible = false;
		m_blinkRemain = 0.4f;
		m_blinkAccum = 0.f;
	}

	m_currentHp -= Dmg;
	if (m_currentHp < 0) m_currentHp = 0;

	// 체력바 값 갱신 (UnitObject가 보관한 포인터에 직접 세팅)
	if (m_healthBar && m_unitData) {
		m_healthBar->SetValue(m_currentHp, m_maxHp);
	}

	// 데미지 플로팅 생성
	Scene* scene = GET_SINGLE(SceneManager)->GetCurScene();
	Vec2 pos = GetPos();
	auto* df = new DamageFloat(std::format(L"-{}", Dmg), RGB(255, 60, 60), 2.f);
	df->SetPos({ pos.x,pos.y - 100 });
	df->SetSize({ 120.f, 40.f }); // 텍스트 박스 크기
	scene->AddObject(df, Layer::CARD);

	return m_currentHp <= 0;
}

void UnitObject::Heal(int heal, bool _floating)
{
	m_currentHp += heal;
	if (m_currentHp > m_maxHp)
		m_currentHp = m_maxHp;
	// 체력바 값 갱신 (UnitObject가 보관한 포인터에 직접 세팅)
	if (m_healthBar)
		m_healthBar->SetValue(m_currentHp, m_unitData ? m_maxHp : 0);

	// 힐 플로팅 생성
	if (_floating) {
		Scene* scene = GET_SINGLE(SceneManager)->GetCurScene();
		Vec2 pos = GetPos();
		auto* df = new DamageFloat(std::format(L"+{}", heal), RGB(60, 255, 60), 2.f);
		df->SetPos({ pos.x,pos.y - 100 });
		df->SetSize({ 120.f, 40.f }); // 텍스트 박스 크기
		scene->AddObject(df, Layer::CARD);
	}
}

bool UnitObject::NeedHeal()
{
	float hpRatio = 0.6f;//현재 hp가 0.6 이하일 때 힐 필요
	return m_currentHp <= (m_maxHp * hpRatio);
}

int UnitObject::GetStat(StatType _type) const
{
	return m_statData->GetStat(_type);
}

bool UnitObject::IsStrongAgainst(ElementType attacker) const
{
	ElementType defender = m_unitData->GetElementType();
	if ((attacker == ElementType::Fire && defender == ElementType::Ice) ||
		(attacker == ElementType::Water && defender == ElementType::Fire) ||
		(attacker == ElementType::Ice && defender == ElementType::Grass) ||
		(attacker == ElementType::Grass && defender == ElementType::Water))
	{
		return true;
	}
	return false;
}

bool UnitObject::IsWeakAgainst(ElementType attacker) const
{
	ElementType defender = m_unitData->GetElementType();
	if ((defender == ElementType::Fire && attacker == ElementType::Ice) ||
		(defender == ElementType::Water && attacker == ElementType::Fire) ||
		(defender == ElementType::Ice && attacker == ElementType::Grass) ||
		(defender == ElementType::Grass && attacker == ElementType::Water))
	{
		return true;
	}
	return false;
}

void UnitObject::ResetStat()
{
	InitStats(0);
}


void UnitObject::StartRevive()
{
	m_isReviving = true;
	m_reviveTimeLeft = m_reviveDuration;

	// 시작 직후 짧은 블링크로 임팩트
	m_isBlinking = true;
	m_isBlinkVisible = false;
	m_blinkRemain = 0.25f;
	m_blinkAccum = 0.f;
}

void UnitObject::UpdateBlink(float dt)
{
	if (!m_isBlinking) return;
	m_blinkRemain -= dt;
	m_blinkAccum += dt;

	if (m_blinkRemain <= 0.f) {
		m_isBlinking = false;
		m_isBlinkVisible = true;
	}
	else if (m_blinkAccum >= m_blinkInterval) {
		m_isBlinkVisible = !m_isBlinkVisible;
		m_blinkAccum = 0.f;
	}
}

void UnitObject::UpdateRevive(float dt)
{
	if (!m_isReviving) return;
	m_reviveTimeLeft -= dt;
	if (m_reviveTimeLeft <= 0.f) {
		m_isReviving = false;
	}
}

void UnitObject::Update()
{
	Object::Update(); // 기존 동작 유지

	// fDT를 사용해 시간 누적
	const float dt = fDT;
	UpdateBlink(dt);
	UpdateRevive(dt);
}

UnitObject::UnitObject()
{
	m_arrowTex = GET_SINGLE(ResourceManager)->GetTexture(L"DownArrow");
}

UnitObject::~UnitObject()
{
	if (m_statData) {
		SAFE_DELETE(m_statData);
	}
	if (m_healthBar) {
		SAFE_DELETE(m_healthBar);
	}
}


void UnitObject::RenderSelection(HDC _hdc, const Vec2& pos, const Vec2& size)
{
	if (!m_isSelect) return;

	LONG width = m_arrowTex->GetWidth();
	LONG height = m_arrowTex->GetHeight();

	// 화살표를 유닛 위쪽 중앙에 원본 크기 그대로 그리기
	int arrowX = (int)(pos.x - width / 2);                    // 중앙 정렬
	int arrowY = (int)(pos.y - size.y / 2 - height - 10);     // 유닛 위 + 간격 10px

	::TransparentBlt(_hdc
		, arrowX              // 목적지 X 좌표 (화살표 중앙이 유닛 중앙에 오도록)
		, arrowY              // 목적지 Y 좌표 (유닛 위쪽)
		, (int)width          // 목적지 폭 (원본 크기 그대로)
		, (int)height         // 목적지 높이 (원본 크기 그대로)
		, m_arrowTex->GetTextureDC()
		, 0, 0                // 원본 시작 위치
		, width, height       // 원본 크기
		, RGB(255, 0, 255));
}

void UnitObject::RenderTexture(HDC _hdc, const Vec2& pos, const Vec2& size, Texture* tex)
{
	LONG width = tex->GetWidth();
	LONG height = tex->GetHeight();

	// 블링크 상태일 때만 본체 숨김
	if (!m_isBlinking || m_isBlinkVisible) {
		::TransparentBlt(_hdc
			, (int)(pos.x - size.x / 2)
			, (int)(pos.y - size.y / 2)
			, (int)size.x
			, (int)size.y
			, tex->GetTextureDC()
			, 0, 0, width, height, RGB(255, 0, 255));
	}
}

void UnitObject::SyncHealthBar(const Vec2& pos, const Vec2& size, float liftY)
{
	if (!m_healthBar) return;

	float barW = size.x * 1.0f;
	float barH = 18.f;
	float barY = pos.y + size.y * 0.5f + 12.f - liftY;
	m_healthBar->SetPos({ pos.x, barY });
	m_healthBar->SetSize({ barW, barH });
}

void UnitObject::RenderNameLeftOfBar(HDC _hdc, const wstring& name, float barW, float barH, float barY, float posX)
{
	float nameBoxW = std::max(100.f, barW * 0.5f); // 최소 폭 확보
	float nameBoxH = barH;

	RECT nameRc{
		(LONG)(posX - barW * 0.5f - 8.f - nameBoxW), // 바 왼쪽보다 약간 더 왼쪽으로
		(LONG)(barY - nameBoxH * 0.5f),
		(LONG)(posX - barW * 0.5f - 8.f),             // 바 왼쪽 바로 옆
		(LONG)(barY + nameBoxH * 0.6f)
	};

	int oldBk = ::SetBkMode(_hdc, TRANSPARENT);
	COLORREF oldColor = ::SetTextColor(_hdc, RGB(255, 255, 255));
	{
		GDISelector fontSel(_hdc, FontType::PIXEL_NORMAL);
		// 본문
		::SetTextColor(_hdc, RGB(0, 0, 0));
		::DrawTextW(_hdc, name.c_str(), (int)name.length(), &nameRc, DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
	}
	::SetTextColor(_hdc, oldColor);
	::SetBkMode(_hdc, oldBk);
}

void UnitObject::Render(HDC _hdc)
{
	// 체력바는 먼저 그려도 되고, 이후 동기화
	if (m_healthBar) m_healthBar->Render(_hdc);

	Vec2 pos = GetPos();
	Vec2 size = GetSize();

	// 리바이브 중이면 스케일/리프트 적용
	float scale = 1.0f;
	float liftY = 0.f;
	if (m_isReviving) {
		float t = 1.f - (m_reviveTimeLeft / m_reviveDuration); // 0→1
		float ease = 0.5f - 0.5f * cosf(t * PI);               // 부드러운 이징
		scale = 0.85f + 0.15f * ease;
		liftY = m_reviveLift * (1.f - ease);
	}

	Vec2 drawSize = { size.x * scale, size.y * scale };
	Vec2 drawPos = { pos.x, pos.y - liftY };

	RenderSelection(_hdc, drawPos, drawSize);

	Texture* tex = m_unitData->GetTexture();
	RenderTexture(_hdc, drawPos, drawSize, tex);

	// 리바이브 하이라이트 테두리(짧게)
	if (m_isReviving) {
		GDISelector penSel(_hdc, PenType::YELLOW);
		GDISelector brushSel(_hdc, BrushType::HOLLOW);
		RECT_RENDER(_hdc, drawPos.x, drawPos.y, drawSize.x * 1.1f, drawSize.y * 1.1f);
	}

	// 체력바 위치/사이즈 동기화 (리프트 반영)
	SyncHealthBar(pos, size, liftY);

	// 이름 텍스트(체력바 왼쪽에 출력)
	if (m_healthBar && m_unitData)
	{
		float barW = size.x * 1.0f;
		float barH = 18.f;
		float barY = pos.y + size.y * 0.5f + 12.f - liftY;
		RenderNameLeftOfBar(_hdc, m_unitData->GetName(), barW, barH, barY, pos.x);
	}
}
void UnitObject::ResetBlink()
{
	m_isBlinking = false;
	m_isBlinkVisible = true;
	m_blinkRemain = 0.f;
	m_blinkAccum = 0.f;
}