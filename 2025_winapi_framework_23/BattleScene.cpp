#include "pch.h"
#include "BattleScene.h"
#include "InputManager.h"
#include "CombatManager.h"
#include "CardObject.h"
#include "Button.h"
#include "ButtonSwitcher.h"
#include "DescriptionText.h"
#include "BattleDescription.h"
#include "CardData.h"
#include "UnitInfoObj.h"
#include "UnitObject.h"
#undef max;

void BattleScene::Init()
{

	int cardWidth = 48 * 4;
	int cardHeight = 64 * 4;
	int margin = 15;

	for (int i = 0; i < 4; ++i)
	{
		CardObject* cardObj = new CardObject();
		cardObj->SetSize({ (float)cardWidth,(float)cardHeight });

		float centerX = margin + cardWidth * 0.5f + i * (cardWidth + margin);
		float centerY = WINDOW_HEIGHT - cardHeight * 0.5f - margin;

		cardObj->SetPos({ centerX, centerY });

		AddObject(cardObj, Layer::CARD);
		m_cardObjs.push_back(cardObj);
	}
	m_uiType = UIType::HAND;
	m_handIndex = 0;
	if (!m_cardObjs.empty())
		m_cardObjs[0]->SetSelect(true);

#pragma region ButtonSwitcher Setting
	ButtonSwitcher* buttonSwitcher = new ButtonSwitcher;
	AddObject(buttonSwitcher, Layer::UI);

	vector<Button*> buttons;
	for (int i = 0; i < 3; i++)
	{
		Button* obj = new Button;
		obj->SetPos({ WINDOW_WIDTH - 80, (45 * i) + 560 });
		obj->SetSize({ 150,40 });
		AddObject(obj, Layer::DEFAULT);

		switch (i)
		{
		case 0:
		{
			obj->SetOnClick([this]() {
				m_uiType = UIType::HAND;
				OnOffHand(true);
				OnOffInfo(false);
				}, "UIType::HAND으로 변경");
		}
		break;
		case 1:
		{
			obj->SetOnClick([this]() {
				m_uiType = UIType::INFO;
				OnOffHand(false);
				OnOffInfo(true);
				}, "UIType::INFO으로 변경");
		}
		break;
		case 2:
		{
			obj->SetOnClick([this]() {
				m_uiType = UIType::DECK;
				OnOffHand(false);
				OnOffInfo(false);
				}, "UIType::DECK으로 변경");
		}
		break;
		default:
			break;
		}

		buttons.push_back(obj);
	}

	buttonSwitcher->SetButtons(buttons);
	SetCardData();

#pragma endregion

	// DescriptionText를 카드와 버튼 사이 공간에 배치
	{
		// 오른쪽 카드의 오른쪽 모서리 X
		float rightCardRight = (float)(4 * (cardWidth + margin)); // = 828
		// 버튼 왼쪽 모서리 X (버튼 중심 X: WINDOW_WIDTH-80, 반폭 75)
		float buttonLeft = (float)((WINDOW_WIDTH - 80) - 75);     // = 1125
		float spacing = 15.f;

		float left = rightCardRight + spacing;
		float right = buttonLeft - spacing;
		float width = std::max(120.f, right - left);
		float height = cardHeight * 0.6f; // 카드 높이의 60% 정도
		float centerX = (left + right) * 0.5f;
		float centerY = (float)(WINDOW_HEIGHT - cardHeight * 0.5f - margin); // 카드 중앙 Y와 맞춤

		m_descriptionText = new DescriptionText;
		m_descriptionText->SetPos({ centerX, centerY });
		m_descriptionText->SetSize({ width, height });
		if (!m_cardObjs.empty())
			m_descriptionText->SetTargetCard(m_cardObjs[m_handIndex]); // 현재 선택 카드로 초기화
		AddObject(m_descriptionText, Layer::UI);
	}

	// 총 너비 = 4*cardWidth + 3*margin, 중앙 X = 첫 카드 왼쪽 + 총 너비/2
	float totalWidth = (4.f * cardWidth) + (3.f * margin);
	float rowCenterY = WINDOW_HEIGHT - cardHeight * 0.5f - margin;
	float firstCardLeft = (margin + cardWidth * 0.5f) - (cardWidth * 0.5f);
	float bdCenterX = firstCardLeft + totalWidth * 0.5f;

	float bdWidth = totalWidth;
	float bdHeight = cardHeight; // 카드 높이와 동일(필요 시 조정)
	{
		m_battleDescription = new BattleDescription;
		m_battleDescription->SetPos({ bdCenterX, rowCenterY });
		m_battleDescription->SetSize({ bdWidth, bdHeight });
		m_battleDescription->SetActive(false);
		AddObject(m_battleDescription, Layer::UI);
	}
	{
		m_unitInfoObj = new UnitInfoObj;
		m_unitInfoObj->SetPos({ bdCenterX, rowCenterY });
		m_unitInfoObj->SetSize({ bdWidth, bdHeight });
		m_unitInfoObj->SetActive(false);
		AddObject(m_unitInfoObj, Layer::UI);
	}
}

void BattleScene::Update()
{
	Scene::Update();

	if (m_waitTurn) {
		GET_SINGLE(CombatManager)->Update();
		return;
	}
	if (m_uiType == UIType::HAND)
		SelectHand();
}

void BattleScene::Render(HDC _hdc)
{
	Scene::Render(_hdc);
	GET_SINGLE(CombatManager)->Render(_hdc);
}

void BattleScene::Release()
{
	Scene::Release();
	m_cardObjs.clear();
	m_descriptionText = nullptr;
}
void BattleScene::OnOffInfo(bool _isOn)
{
	if (m_waitTurn) return;
	if (_isOn == true) {
		UnitType targetUnit = AskTargetUnit();
		m_unitInfoObj->SetInfo(GET_SINGLE(CombatManager)->GetUnit(targetUnit)->GetStatData());
	}

	if (m_unitInfoObj)
		m_unitInfoObj->SetActive(_isOn);
}
void BattleScene::OnOffHand(bool _isOn)
{
	if (m_waitTurn) return;
	for (auto card : m_cardObjs)
	{
		card->SetActive(_isOn);
	}
	if (m_descriptionText) m_descriptionText->SetActive(_isOn);
}

void BattleScene::SelectHand()
{
	if (m_cardObjs.size() < 4) return;

	bool changed = false;
	if (GET_KEYUP(KEY_TYPE::LEFT) || GET_KEYUP(KEY_TYPE::A))
	{
		m_handIndex = (m_handIndex + 3) % 4;
		changed = true;
	}
	else if (GET_KEYUP(KEY_TYPE::RIGHT) || GET_KEYUP(KEY_TYPE::D))
	{
		m_handIndex = (m_handIndex + 1) % 4;
		changed = true;
	}

	if (changed)
	{
		for (int i = 0; i < 4; ++i)
			m_cardObjs[i]->SetSelect(i == m_handIndex);
		if (m_descriptionText)
			m_descriptionText->SetTargetCard(m_cardObjs[m_handIndex]); // 설명 대상 갱신
	}

	if (GET_KEYUP(KEY_TYPE::C))
	{
		if (m_waitTurn) return;
		UnitType target = UnitType::SELF;
		CardEffectType effectType = m_cardObjs[m_handIndex]->GetCardData()->GetCardEffect();
		if (effectType != CardEffectType::StatBuff&& effectType!=CardEffectType::Shield) {
			target = AskTargetUnit();
		}
		GET_SINGLE(CombatManager)->AddAction(target, m_handIndex);
		SetCardData();
	}
}



UnitType BattleScene::AskTargetUnit()
{
	HWND hwndOwner = GetActiveWindow();
	int ret = ::MessageBoxW(
		hwndOwner,
		L"대상 유닛을 선택하세요:\n\nYes : Player1\nNo : Player2\nCancel : Enemy",
		L"유닛 선택",
		MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON1
	);

	switch (ret)
	{
	case IDYES:    return UnitType::PLAYER1;
	case IDNO:     return UnitType::PLAYER2;
	case IDCANCEL: return UnitType::ENEMY;
	default:       return UnitType::ENEMY;
	}
}

void BattleScene::SetDes(ActionData* data)
{
	if (m_battleDescription)
		m_battleDescription->SetText(data);
}

void BattleScene::SetCardData()
{
	vector<CardData*> handCards = GET_SINGLE(CombatManager)->GetHandCard();
	int n = std::min<int>(4, (int)handCards.size());
	for (int i = 0; i < n && i < (int)m_cardObjs.size(); ++i)
	{
		if (m_cardObjs[i])
			m_cardObjs[i]->SetCardData(handCards[i]);
	}
}

void BattleScene::SetWaitTurn(bool _isWait)
{
	m_waitTurn = _isWait;

	for (CardObject* card : m_cardObjs)
	{
		card->SetActive(!m_waitTurn);
	}
	if (m_descriptionText)
		m_descriptionText->SetActive(!m_waitTurn);
	if (m_battleDescription) {
		m_battleDescription->SetActive(m_waitTurn);
	}
}
