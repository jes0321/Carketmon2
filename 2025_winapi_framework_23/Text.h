#pragma once
#include "Object.h"
class Text :
    public Object
{
public:
    Text(std::wstring _text);
	~Text();
public:
	void Render(HDC _hdc) override;
public:
	void SetText(std::wstring _text) { m_text = _text; }
	std::wstring GetText() const { return m_text; }
private:
	std::wstring m_text;
};

