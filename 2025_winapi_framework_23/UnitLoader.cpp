#include <fstream>
#include <sstream>
#include "pch.h"
#include "UnitData.h"
#include "CardData.h"
// 문자열 → ElementType 변환


// CSV 문자열 → wstring 변환용
std::wstring s2ws(const std::string& s)
{
    return std::wstring(s.begin(), s.end());
}

void LoadUnitStatsCSV(const std::wstring& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        MessageBox(NULL, L"unit_stats.csv 파일을 찾을 수 없습니다.", L"Error", MB_OK);
        return;
    }

    std::string line;
    getline(file, line); // 첫 줄(헤더) 버림

    while (getline(file, line))
    {
        std::stringstream ss(line);

        std::string name, code, element;
        int hp, atk, def, spd;

        getline(ss, name, ',');
        getline(ss, code, ',');
        ss >> hp; ss.ignore();
        ss >> atk; ss.ignore();
        ss >> def; ss.ignore();
        ss >> spd; ss.ignore();
        getline(ss, element, ',');

        UnitData* data = RegisterUnit(
            s2ws(name), s2ws(code), StringToElement(s2ws(element))
        );

        data->SetStats(hp, atk, def, spd);
    }
}

void LoadUnitCardsCSV(const std::wstring& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        MessageBox(NULL, L"unit_cards.csv 파일을 찾을 수 없습니다.", L"Error", MB_OK);
        return;
    }

    CardManager* cardManager = GET_SINGLE(CardManager);

    std::string line;
    getline(file, line); // 헤더 제거

    while (getline(file, line))
    {
        std::stringstream ss(line);
        std::string name, cardName;
        int count;

        getline(ss, name, ',');
        getline(ss, cardName, ',');
        ss >> count;

        UnitData* unit = FindUnitByName(s2ws(name));
        if (unit == nullptr) continue;

        unit->SetCard(cardManager->GetCard(s2ws(cardName)), count);
    }
}
