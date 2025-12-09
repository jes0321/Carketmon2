#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
bool ResourceManager::Init()
{
	//fs::path curPath = fs::current_path();
	//m_resourcePath = curPath.parent_path() / L"Output\\build\\Resource\\";
	wchar_t buf[MAX_PATH] = {}; // windows 최대 경로 길이
	::GetModuleFileNameW(nullptr, buf, MAX_PATH); // 현재 실행중인 exe 경로 buf에 저장   
	fs::path exeDir = fs::path(buf).parent_path();                //  buf 전체 경로를 path 객체로 가서 디렉토리만 추출
	fs::path resourceDir = exeDir.parent_path() / L"build" / L"Resource\\"; // release모드일때 build 한번더 붙이는거 무시
	m_resourcePath = resourceDir.native();

	if (!RegisterFontFile(L"Font\\나눔손글씨 암스테르담.ttf"))
		return false;
	if (!RegisterFontFile(L"Font\\Galmuri7.ttf"))
		return false;
	if (!RegisterFontFile(L"Font\\neodgm.ttf"))
		return false;
	RegisterTexture();
	RegisterGDI();

	FMOD::System_Create(&m_pSoundSystem);
	if (m_pSoundSystem != nullptr)
		m_pSoundSystem->init(64, FMOD_INIT_NORMAL, nullptr);
	RegisterSound();
	return true;
}

void ResourceManager::FmodUpdate()
{
	if (m_pSoundSystem != nullptr)
		m_pSoundSystem->update();
}

void ResourceManager::Release()
{
	std::unordered_map<wstring, Texture*>::iterator iter;
	for (iter = m_mapTextures.begin(); iter != m_mapTextures.end(); ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	m_mapTextures.clear();

	ReleaseGDI();
	ReleaseFonts();

	std::unordered_map<wstring, SoundInfo*>::iterator iterSound;
	for (iterSound = m_mapSounds.begin(); iterSound != m_mapSounds.end(); ++iterSound)
		SAFE_DELETE(iterSound->second);
	m_mapSounds.clear();

	m_pSoundSystem->close();
	m_pSoundSystem->release();
}
void ResourceManager::RegisterTexture()
{
#pragma region Cacketmons
	LoadTexture(L"Fire_Rat", L"Texture\\Cacketmons\\Fire_Rat_32x32.bmp");
	LoadTexture(L"Fire_Turtle", L"Texture\\Cacketmons\\Fire_Turtle_32x32.bmp");
	LoadTexture(L"Water_FishFox", L"Texture\\Cacketmons\\Water_FishFox_32x32.bmp");
	LoadTexture(L"Water_FishKing", L"Texture\\Cacketmons\\Water_FishKing_32x32.bmp");
	LoadTexture(L"Water_SquidGirl", L"Texture\\Cacketmons\\Water_SquidGirl_32x32.bmp");
#pragma endregion

#pragma region Card
	LoadTexture(L"Fireball", L"Texture\\Cards\\Fireball_48x64.bmp");
	LoadTexture(L"Flamethrower", L"Texture\\Cards\\Flamethrower_48x64.bmp");
	LoadTexture(L"WaterSurfing", L"Texture\\Cards\\Surfing_48x64.bmp");
	LoadTexture(L"WaterCannon", L"Texture\\Cards\\WaterCannon_48x64.bmp");
	LoadTexture(L"WaterShuriken", L"Texture\\Cards\\WaterShuriken_48x64.bmp");

	LoadTexture(L"CuttingGrass", L"Texture\\Cards\\CuttingGrass.bmp");
	LoadTexture(L"GrassLeafFalls", L"Texture\\Cards\\GrassLeafFalls.bmp");
	LoadTexture(L"Ice_Shuriken", L"Texture\\Cards\\Ice_Shuriken.bmp");
	LoadTexture(L"Icicle", L"Texture\\Cards\\Icicle.bmp");
	LoadTexture(L"PoisonThorn", L"Texture\\Cards\\PoisonThorn.bmp");
	LoadTexture(L"ThornVine", L"Texture\\Cards\\ThornVine.bmp");
#pragma endregion

#pragma region UI
	LoadTexture(L"Button_Deck_Default", L"Texture\\UI\\Button_Deck_Default.bmp");
	LoadTexture(L"Button_Deck_Select", L"Texture\\UI\\Button_Deck_Select.bmp");
	LoadTexture(L"Button_Deck_Click", L"Texture\\UI\\Button_Deck_Click.bmp");
	LoadTexture(L"Button_Hand_Default", L"Texture\\UI\\Button_Hand_Default.bmp");
	LoadTexture(L"Button_Hand_Select", L"Texture\\UI\\Button_Hand_Select.bmp");
	LoadTexture(L"Button_Hand_Click", L"Texture\\UI\\Button_Hand_Click.bmp");
	LoadTexture(L"Button_Info_Default", L"Texture\\UI\\Button_Info_Default.bmp");
	LoadTexture(L"Button_Info_Select", L"Texture\\UI\\Button_Info_Select.bmp");
	LoadTexture(L"Button_Info_Click", L"Texture\\UI\\Button_Info_Click.bmp");
	LoadTexture(L"Button_Start_Default", L"Texture\\UI\\Button_Start_Default.bmp");
	LoadTexture(L"Button_Start_Select", L"Texture\\UI\\Button_Start_Select.bmp");
	LoadTexture(L"Button_Start_Click", L"Texture\\UI\\Button_Start_Click.bmp");
	LoadTexture(L"Button_Cancel_Default", L"Texture\\UI\\Button_Cancel_Default.bmp");
	LoadTexture(L"Button_Cancel_Select", L"Texture\\UI\\Button_Cancel_Select.bmp");
	LoadTexture(L"Button_Cancel_Click", L"Texture\\UI\\Button_Cancel_Click.bmp");

	LoadTexture(L"Mark_Fire", L"Texture\\UI\\Mark_Fire_Element.bmp");
	LoadTexture(L"Mark_Water", L"Texture\\UI\\Mark_Water_Element.bmp");
	LoadTexture(L"Mark_Leaf", L"Texture\\UI\\Mark_Leaf_Element.bmp");
	LoadTexture(L"Mark_Ice", L"Texture\\UI\\Mark_Ice_Element.bmp");
#pragma endregion

}
void ResourceManager::RegisterGDI()
{
	// BRUSH
	m_Brushs[(UINT)BrushType::HOLLOW] = (HBRUSH)::GetStockObject(HOLLOW_BRUSH);
	m_Brushs[(UINT)BrushType::RED] = (HBRUSH)::CreateSolidBrush(RGB(255, 167, 167));
	m_Brushs[(UINT)BrushType::GREEN] = (HBRUSH)::CreateSolidBrush(RGB(134, 229, 134));
	m_Brushs[(UINT)BrushType::BLUE] = (HBRUSH)::CreateSolidBrush(RGB(167, 167, 255));

	// PEN 
	m_Pens[(UINT)PenType::RED] = ::CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_Pens[(UINT)PenType::GREEN] = ::CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_Pens[(UINT)PenType::BOLD_GREEN] = ::CreatePen(PS_SOLID, 5, RGB(0, 255, 0));
	m_Pens[(UINT)PenType::BOLD_GRAY] = ::CreatePen(PS_SOLID, 5, RGB(128, 128, 128));
	m_Pens[(UINT)PenType::YELLOW] = ::CreatePen(PS_SOLID, 1, RGB(255, 220, 0));

	// 폰트 등록
	RegisterFont(FontType::TITLE, L"나눔손글씨 암스테르담", 0);
	RegisterFont(FontType::UI, L"나눔손글씨 암스테르담", 0);
	RegisterFont(FontType::BIG_UI, L"나눔손글씨 암스테르담", -48, FW_BOLD);
	RegisterFont(FontType::BOLD_UI, L"나눔손글씨 암스테르담", -18, FW_BOLD);
	RegisterFont(FontType::PIXEL_BIG, L"neodgm", -24, FW_BOLD, false, NONANTIALIASED_QUALITY);
	RegisterFont(FontType::PIXEL_MIDIUM, L"Galmuri7", -18, FW_BOLD, false, NONANTIALIASED_QUALITY);
	RegisterFont(FontType::PIXEL_NORMAL, L"Galmuri7", -12,FW_BOLD, false, NONANTIALIASED_QUALITY);
	//RegisterFont(FontType::PIXEL_NORMAL, L"neodgm", 0, false, NONANTIALIASED_QUALITY);
}
void ResourceManager::ReleaseGDI()
{
	for (int i = 0; i < (UINT)PenType::END; ++i)
		::DeleteObject(m_Pens[i]);
	for (int i = 1; i < (UINT)BrushType::END; ++i)
		// Hollow 제외하고
		::DeleteObject(m_Brushs[i]);
	for (int i = 0; i < (UINT)FontType::END; ++i)
		::DeleteObject(m_Fonts[i]);
}
bool ResourceManager::RegisterFontFile(const wstring& _path)
{
	wstring fontPath = m_resourcePath;
	fontPath += _path;
	if (!(AddFontResourceExW(fontPath.c_str(), FR_PRIVATE, 0) > 0))
		return false;
	m_vecFontFiles.push_back(fontPath);
	return true;
}

void ResourceManager::ReleaseFonts()
{
	for (const auto& path : m_vecFontFiles)
		::RemoveFontResourceExW(path.c_str(), FR_PRIVATE, 0);
	m_vecFontFiles.clear();
}
void ResourceManager::RegisterFont(FontType _type, const wstring& _name, int _height, int _weight, bool _italic, int _quality)
{

	HFONT h = ::CreateFont(_height, 0, 0, 0, _weight, _italic, false, false, HANGEUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, _quality, DEFAULT_PITCH || FF_DONTCARE, _name.c_str());
	m_Fonts[(UINT)_type] = h;

}
void ResourceManager::LoadSound(const wstring& _key, const wstring& _path, bool _isLoop)
{
	if (FindSound(_key) || !m_pSoundSystem)
		return;
	wstring strFilePath = m_resourcePath;
	strFilePath += _path;

	// wstring to string
	std::string str;
	str.assign(strFilePath.begin(), strFilePath.end());

	// 루프할지 말지 결정
	FMOD_MODE eMode = FMOD_LOOP_NORMAL; // 반복 출력
	if (!_isLoop)
		eMode = FMOD_DEFAULT; // 사운드 1번만 출력
	FMOD::Sound* p = nullptr;

	// BGM면 stream, 아니면 sound
	// 팩토리함수
	//// 사운드 객체를 만드는 것은 system임.
	//						//파일경로,  FMOD_MODE, NULL, &sound
	FMOD_RESULT r = _isLoop
		? m_pSoundSystem->createStream(str.c_str(), eMode, nullptr, &p)
		: m_pSoundSystem->createSound(str.c_str(), eMode, nullptr, &p);

	if (r != FMOD_OK || !p)
		return;

	SoundInfo* pSound = new SoundInfo;
	pSound->IsLoop = _isLoop;
	pSound->pSound = p;
	m_mapSounds.insert({ _key, pSound });

}

void ResourceManager::Play(const wstring& _key)
{
	SoundInfo* pSound = FindSound(_key);
	if (!pSound)
		return;
	SOUND_CHANNEL eChannel = SOUND_CHANNEL::BGM;
	if (!pSound->IsLoop)
		eChannel = SOUND_CHANNEL::EFFECT;
	// 사운드 재생 함수. &channel로 어떤 채널을 통해 재생되는지 포인터 넘김
	m_pSoundSystem->playSound(pSound->pSound, nullptr, false, &m_pChannel[(UINT)eChannel]);

}

void ResourceManager::Stop(SOUND_CHANNEL _channel)
{
	m_pChannel[(UINT)_channel]->stop();

}

void ResourceManager::Volume(SOUND_CHANNEL _channel, float _vol)
{
	// 0.0 ~ 1.0 볼륨 조절
	m_pChannel[(UINT)_channel]->setVolume(_vol);

}

void ResourceManager::Pause(SOUND_CHANNEL _channel, bool _ispause)
{
	m_pChannel[(UINT)_channel]->setPaused(_ispause);
}
SoundInfo* ResourceManager::FindSound(const wstring& _key)
{
	std::unordered_map<wstring, SoundInfo*>::iterator iter = m_mapSounds.find(_key);

	if (iter == m_mapSounds.end())
		return nullptr;
	return iter->second;
}


void ResourceManager::LoadTexture(const wstring& _key, const wstring& _path)
{
	Texture* tex = GetTexture(_key);
	if (nullptr != tex)
		return;

	// 생성
	wstring texPath = m_resourcePath;
	texPath += _path;

	tex = new Texture;
	tex->Load(texPath);
	tex->SetKey(_key);
	tex->SetRelativePath(texPath);
	m_mapTextures.insert({ _key, tex });
}

Texture* ResourceManager::GetTexture(const wstring& _key)
{
	auto iter = m_mapTextures.find(_key);
	if (iter != m_mapTextures.end())
		return iter->second;
	return nullptr;
}


void ResourceManager::RegisterSound()
{
	LoadSound(L"BGM",L"Sound\\Retro_bgm.wav",true);
	LoadSound(L"BATTLEBGM",L"Sound\\RedBGM.wav",true);
	LoadSound(L"Btn",L"Sound\\btn_sound.wav",false);
}
