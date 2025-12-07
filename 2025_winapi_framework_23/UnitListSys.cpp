#include "pch.h"
#include "UnitListSys.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <windows.h>

namespace fs = std::filesystem;

static std::wstring Utf8ToWide(const std::string& s) {
    if (s.empty()) return L"";
    int wlen = ::MultiByteToWideChar(CP_UTF8, 0, s.c_str(), (int)s.size(), nullptr, 0);
    std::wstring w; w.resize(wlen);
    ::MultiByteToWideChar(CP_UTF8, 0, s.c_str(), (int)s.size(), &w[0], wlen);
    return w;
}
static std::string WideToUtf8(const std::wstring& w) {
    if (w.empty()) return "";
    int len = ::WideCharToMultiByte(CP_UTF8, 0, w.c_str(), (int)w.size(), nullptr, 0, nullptr, nullptr);
    std::string s; s.resize(len);
    ::WideCharToMultiByte(CP_UTF8, 0, w.c_str(), (int)w.size(), &s[0], len, nullptr, nullptr);
    return s;
}

std::wstring UnitListSys::GetUnitListPath()
{
    wchar_t buf[MAX_PATH] = {};
    ::GetModuleFileNameW(nullptr, buf, MAX_PATH);
    fs::path exeDir = fs::path(buf).parent_path();
    fs::path resourceDir = exeDir.parent_path() / L"build" / L"Resource\\";
    fs::path txtPath = resourceDir / L"Texture\\UnitList.txt";
    return txtPath.wstring();
}

std::vector<std::wstring> UnitListSys::ReadNames()
{
    std::vector<std::wstring> names;
    std::wstring path = GetUnitListPath();

    std::ifstream fin(fs::path(path).string(), std::ios::binary);
    if (!fin.is_open()) return names;

    // UTF-8 BOM 처리 후 첫 줄만 읽기
    char bom[3] = {};
    fin.read(bom, 3);
    if (!(bom[0] == char(0xEF) && bom[1] == char(0xBB) && bom[2] == char(0xBF))) {
        fin.seekg(0);
    }
    std::string line;
    std::getline(fin, line);
    fin.close();

    std::wstring content = Utf8ToWide(line);
    std::wstringstream ss(content);
    std::wstring token;
    while (std::getline(ss, token, L',')) {
        token.erase(0, token.find_first_not_of(L" \t\r\n"));
        if (!token.empty())
            token.erase(token.find_last_not_of(L" \t\r\n") + 1);
        if (!token.empty())
            names.push_back(token);
    }
    return names;
}

bool UnitListSys::Exists(const std::wstring& name)
{
    auto names = ReadNames();
    return std::find(names.begin(), names.end(), name) != names.end();
}

bool UnitListSys::AppendIfNotExists(const std::wstring& name)
{
    auto names = ReadNames();
    if (std::find(names.begin(), names.end(), name) != names.end())
        return false;

    names.push_back(name);

    // CSV 직렬화
    std::wstring joined;
    for (size_t i = 0; i < names.size(); ++i) {
        if (i) joined += L",";
        joined += names[i];
    }

    // UTF-8 BOM 포함 저장 (첫 줄만)
    std::wstring path = GetUnitListPath();
    std::ofstream fout(fs::path(path).string(), std::ios::binary | std::ios::trunc);
    if (!fout.is_open()) return false;

    const unsigned char utf8bom[3] = { 0xEF, 0xBB, 0xBF };
    fout.write(reinterpret_cast<const char*>(utf8bom), 3);

    std::string u8 = WideToUtf8(joined);
    fout.write(u8.data(), (std::streamsize)u8.size());
    fout.put('\n');
    fout.close();
    return true;
}