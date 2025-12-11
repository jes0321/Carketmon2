#include "pch.h"
#include "UnitListSys.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <windows.h>

namespace fs = std::filesystem;

/// <summary>
/// UTF-8 인코딩된 문자열을 와이드 문자열(UTF-16)로 변환
/// </summary>
/// <param name="s">UTF-8 문자열</param>
/// <returns>변환된 와이드 문자열</returns>
static std::wstring Utf8ToWide(const std::string& s) {
    if (s.empty()) return L"";
    int wlen = ::MultiByteToWideChar(CP_UTF8, 0, s.c_str(), (int)s.size(), nullptr, 0);
    std::wstring w; w.resize(wlen);
    ::MultiByteToWideChar(CP_UTF8, 0, s.c_str(), (int)s.size(), &w[0], wlen);
    return w;
}

/// <summary>
/// 와이드 문자열(UTF-16)을 UTF-8 인코딩된 문자열로 변환
/// </summary>
/// <param name="w">와이드 문자열</param>
/// <returns>변환된 UTF-8 문자열</returns>
static std::string WideToUtf8(const std::wstring& w) {
    if (w.empty()) return "";
    int len = ::WideCharToMultiByte(CP_UTF8, 0, w.c_str(), (int)w.size(), nullptr, 0, nullptr, nullptr);
    std::string s; s.resize(len);
    ::WideCharToMultiByte(CP_UTF8, 0, w.c_str(), (int)w.size(), &s[0], len, nullptr, nullptr);
    return s;
}

/// <summary>
/// UnitList.txt 파일의 전체 경로를 반환
/// 실행 파일 위치에서 상대 경로로 Resource/Texture/UnitList.txt를 찾음
/// </summary>
/// <returns>UnitList.txt 파일의 절대 경로</returns>
std::wstring UnitListSys::GetUnitListPath()
{
    wchar_t buf[MAX_PATH] = {};
    ::GetModuleFileNameW(nullptr, buf, MAX_PATH);
    fs::path exeDir = fs::path(buf).parent_path();
    fs::path resourceDir = exeDir.parent_path() / L"build" / L"Resource\\";
    fs::path txtPath = resourceDir / L"Texture\\UnitList.txt";
    return txtPath.wstring();
}

/// <summary>
/// UnitList.txt 파일에서 유닛 이름 목록을 읽어옴
/// 파일의 첫 번째 줄만 읽으며, CSV 형식(쉼표로 구분)으로 저장된 유닛 이름들을 파싱
/// UTF-8 BOM을 자동으로 처리
/// </summary>
/// <returns>유닛 이름 목록 (wstring 벡터)</returns>
std::vector<std::wstring> UnitListSys::ReadNames()
{
    std::vector<std::wstring> names;
    std::wstring path = GetUnitListPath();

    // 파일을 바이너리 모드로 열기 (UTF-8 BOM 처리를 위해)
    std::ifstream fin(fs::path(path).string(), std::ios::binary);
    if (!fin.is_open()) return names;

    // UTF-8 BOM 체크 및 건너뛰기
    char bom[3] = {};
    fin.read(bom, 3);
    if (!(bom[0] == char(0xEF) && bom[1] == char(0xBB) && bom[2] == char(0xBF))) {
        // BOM이 없으면 파일 시작으로 되돌림
        fin.seekg(0);
    }

    // 첫 줄만 읽기
    std::string line;
    std::getline(fin, line);
    fin.close();

    // UTF-8 문자열을 와이드 문자열로 변환
    std::wstring content = Utf8ToWide(line);

    // 쉼표(,)를 구분자로 하여 토큰 분리
    std::wstringstream ss(content);
    std::wstring token;
    while (std::getline(ss, token, L',')) {
        // 앞뒤 공백 제거
        token.erase(0, token.find_first_not_of(L" \t\r\n"));
        if (!token.empty())
            token.erase(token.find_last_not_of(L" \t\r\n") + 1);

        // 빈 문자열이 아니면 목록에 추가
        if (!token.empty())
            names.push_back(token);
    }
    return names;
}

/// <summary>
/// 주어진 유닛 이름이 목록에 존재하는지 확인
/// </summary>
/// <param name="name">검색할 유닛 이름</param>
/// <returns>존재하면 true, 없으면 false</returns>
bool UnitListSys::Exists(const std::wstring& name)
{
    auto names = ReadNames();
    return std::find(names.begin(), names.end(), name) != names.end();
}

/// <summary>
/// 유닛 이름이 목록에 없으면 추가하고 파일에 저장
/// 중복된 이름은 추가하지 않음
/// </summary>
/// <param name="name">추가할 유닛 이름</param>
/// <returns>새로 추가되었으면 true, 이미 존재하면 false</returns>
bool UnitListSys::AppendIfNotExists(const std::wstring& name)
{
    auto names = ReadNames();

    // 이미 존재하면 추가하지 않음
    if (std::find(names.begin(), names.end(), name) != names.end())
        return false;

    // 목록에 새 이름 추가
    names.push_back(name);

    // CSV 형식으로 직렬화 (쉼표로 구분)
    std::wstring joined;
    for (size_t i = 0; i < names.size(); ++i) {
        if (i) joined += L",";
        joined += names[i];
    }

    // UTF-8 BOM 포함하여 파일에 저장 (첫 줄만)
    std::wstring path = GetUnitListPath();
    std::ofstream fout(fs::path(path).string(), std::ios::binary | std::ios::trunc);
    if (!fout.is_open()) return false;

    // UTF-8 BOM 쓰기
    const unsigned char utf8bom[3] = { 0xEF, 0xBB, 0xBF };
    fout.write(reinterpret_cast<const char*>(utf8bom), 3);

    // 와이드 문자열을 UTF-8로 변환하여 저장
    std::string u8 = WideToUtf8(joined);
    fout.write(u8.data(), (std::streamsize)u8.size());
    fout.put('\n');
    fout.close();
    return true;
}