// 핵심만 변경: UnitSelectUI로 위임
#include "UnitSelectUI.h"
// ... 기존 include 유지 ...

void StartScene::Init()
{
    m_selectVec.clear();
    m_candidates.clear();
    LoadUnitsFromTxt(L"Texture\\UnitList.txt");

    // 선택 UI 생성/설정
    auto* selectUI = new UnitSelectUI();
    // 씬 내 원하는 위치/사이즈(렌더에는 내부 레이아웃을 사용하므로 pos/size는 기본으로 둬도 됨)
    selectUI->SetPos({ 0.f, 0.f });
    selectUI->SetSize({ (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT });
    selectUI->SetGrid(4, 4);
    selectUI->SetTile(128.f, 128.f);
    selectUI->SetSpacing(24.f, 24.f);
    selectUI->SetLeftArea((float)(WINDOW_WIDTH - 80.f), 75.f);
    selectUI->SetCandidates(m_candidates);
    AddObject(selectUI, Layer::UI);

    // 버튼 스위처
    m_btnManager = new ButtonSwitcher;
    m_btnManager->OnOffInput(false);
    AddObject(m_btnManager, Layer::UI);

    vector<Button*> buttons;
    for (int i = 0; i < 2; i++) {
        Button* obj = new Button;
        obj->SetPos({ WINDOW_WIDTH - 80, (45 * i) + 560 });
        obj->SetSize({ 150,40 });
        AddObject(obj, Layer::DEFAULT);

        switch (i) {
        case 0:
            obj->SetOnClick([this, selectUI]() {
                selectUI->ClearSelection();
                selectUI->SetSelectionEnabled(true);
                m_btnManager->OnOffInput(false);
            }, "취소");
            break;
        case 1:
            obj->SetOnClick([this, selectUI]() {
                const auto& chosen = selectUI->GetSelected();
                if (chosen.size() < 2 || !chosen[0] || !chosen[1]) {
                    selectUI->SetSelectionEnabled(true);
                    m_btnManager->OnOffInput(false);
                    return;
                }
                GET_SINGLE(CombatManager)->SetUnitData(UnitType::PLAYER1, chosen[0]);
                GET_SINGLE(CombatManager)->SetUnitData(UnitType::PLAYER2, chosen[1]);
                GET_SINGLE(SceneManager)->LoadScene(L"StageSelectScene");
            }, "시작");
            break;
        }
        buttons.push_back(obj);
    }
    m_btnManager->SetButtons(buttons);
}

void StartScene::Update()
{
    Scene::Update();

    // 선택 완료되면 버튼 입력 켜기
    // 선택 UI를 찾아 상태 확인
    // 간단히: 씬 오브젝트 순회 없이 버튼만 제어하고 싶으면, 위 버튼 onClick/취소에서만 OnOffInput 토글 유지해도 됨.
}