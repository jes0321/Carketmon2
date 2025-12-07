#pragma once
class UnitListSys
{
public:
    // 공용 유틸: UnitList.txt 경로
    static std::wstring GetUnitListPath();

    // 첫 줄 CSV 읽기 -> 이름 목록
    static std::vector<std::wstring> ReadNames();

    // 중복 검사
    static bool Exists(const std::wstring& name);

    // 중복 없으면 추가 후 저장
    static bool AppendIfNotExists(const std::wstring& name);
};