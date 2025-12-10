#pragma once
#include "Object.h"
#include "Texture.h"
#include "ResourceManager.h"

enum ButtonState
{
	Default,
	Clicked,
	Selected
};

class Button :
	public Object
{
public:
	Button();
	~Button();
public:
	void Render(HDC _hdc);
	void Update() override;
public:
	void SetButtonType(UIType _uiType) 
	{ 
		m_uiType = _uiType; 

		if (_uiType == UIType::NONE) return;

		switch (_uiType)
		{
			case UIType::HAND:
				m_defaultTexture = GET_SINGLE(ResourceManager)
					->GetTexture(L"Button_Hand_Default");
				m_selectedTexture = GET_SINGLE(ResourceManager)
					->GetTexture(L"Button_Hand_Select");
				m_clickedTexture = GET_SINGLE(ResourceManager)
					->GetTexture(L"Button_Hand_Click");
				break;
			case UIType::INFO:
				m_defaultTexture = GET_SINGLE(ResourceManager)
					->GetTexture(L"Button_Info_Default");
				m_selectedTexture = GET_SINGLE(ResourceManager)
					->GetTexture(L"Button_Info_Select");
				m_clickedTexture = GET_SINGLE(ResourceManager)
					->GetTexture(L"Button_Info_Click");
				break;
			case UIType::DECK:
				m_defaultTexture = GET_SINGLE(ResourceManager)
					->GetTexture(L"Button_Deck_Default");
				m_selectedTexture = GET_SINGLE(ResourceManager)
					->GetTexture(L"Button_Deck_Select");
				m_clickedTexture = GET_SINGLE(ResourceManager)
					->GetTexture(L"Button_Deck_Click");
				break;
			case UIType::CANCEL:
				m_defaultTexture = GET_SINGLE(ResourceManager)
					->GetTexture(L"Button_Cancel_Default");
				m_selectedTexture = GET_SINGLE(ResourceManager)
					->GetTexture(L"Button_Cancel_Select");
				m_clickedTexture = GET_SINGLE(ResourceManager)
					->GetTexture(L"Button_Cancel_Click");
				break;
			case UIType::START:
				m_defaultTexture = GET_SINGLE(ResourceManager)
					->GetTexture(L"Button_Start_Default");
				m_selectedTexture = GET_SINGLE(ResourceManager)
					->GetTexture(L"Button_Start_Select");
				m_clickedTexture = GET_SINGLE(ResourceManager)
					->GetTexture(L"Button_Start_Click");
				break;
			case UIType::EXIT:
				m_defaultTexture = GET_SINGLE(ResourceManager)
					->GetTexture(L"Button_Exit_Default");
				m_selectedTexture = GET_SINGLE(ResourceManager)
					->GetTexture(L"Button_Exit_Select");
				m_clickedTexture = GET_SINGLE(ResourceManager)
					->GetTexture(L"Button_Exit_Click");
			case UIType::EXCHANGE:
				m_defaultTexture = GET_SINGLE(ResourceManager)
					->GetTexture(L"Button_Exchange_Default");
				m_selectedTexture = GET_SINGLE(ResourceManager)
					->GetTexture(L"Button_Exchange_Select");
				m_clickedTexture = GET_SINGLE(ResourceManager)
					->GetTexture(L"Button_Exchange_Click");
				break;
			case UIType::SKIP:
				m_defaultTexture = GET_SINGLE(ResourceManager)
					->GetTexture(L"Button_Skip_Default");
				m_selectedTexture = GET_SINGLE(ResourceManager)
					->GetTexture(L"Button_Skip_Select");
				m_clickedTexture = GET_SINGLE(ResourceManager)
					->GetTexture(L"Button_Skip_Click");
				break;
		}
	}
	void SetDefaultTexture(Texture* _texture) { m_defaultTexture = _texture; }
	void SetClickedTexture(Texture* _texture) { m_clickedTexture = _texture; }
	void SetSelectedTexture(Texture* _texture) { m_selectedTexture = _texture; }
	void SetStateTexture(Texture* _default, Texture* _clicked, Texture* _selected)
	{ 
		m_defaultTexture = _default;
		m_clickedTexture = _clicked;
		m_selectedTexture = _selected;
	}
	void SetCurrentexture(Texture* _texture) { m_currnetTexture = _texture; }
	void SetViewRect(bool _isViewRect) { m_isViewRect = _isViewRect; }

	void SetOnClick(std::function<void()> func, std::string message = "")
	{
		m_buttonText = message;
		m_onClick = func;
	}

	void Click()
	{
		if (m_onClick)
		{
			cout << m_buttonText << '\n';
			m_onClick(); // 참조한 함수 실행
		}
	}
public:
	ButtonState m_buttonState = ButtonState::Default;
	Texture* m_defaultTexture = nullptr;
	Texture* m_clickedTexture = nullptr;
	Texture* m_selectedTexture = nullptr;
	Texture* m_currnetTexture = nullptr;
	UIType m_uiType = UIType::NONE;

	std::function<void()> m_onClick;
	std::string m_buttonText = "Button 클릭";
	bool m_isViewRect = false;
};

