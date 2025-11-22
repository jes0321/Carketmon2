#include "pch.h"
#include "Texture.h"
#include "Core.h"
Texture::Texture()
	: m_hBit(nullptr)
	, m_hDC(nullptr)
	, m_bitInfo{}
{
}
void Texture::Load(const wstring& _filePath)
{
	// 1. 인스턴스 핸들 - nullptr - 독립형 리소스
	// 2. 파일 이름 - 경로
	// 3. 타입(파일형식) - 비트맵
	// 4~5. 파일 크기 - 0(파일 원본 크기)
	// 5. 옵션 플래그 
	m_hBit = (HBITMAP)::LoadImage(nullptr, _filePath.c_str(), IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	// 예외처리
	assert(m_hBit);

	m_hDC = ::CreateCompatibleDC(GET_SINGLE(Core)->GetMainDC());
	::SelectObject(m_hDC, m_hBit);

	::GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}

Texture::~Texture()
{
	::DeleteDC(m_hDC);
	::DeleteObject(m_hBit);
}

