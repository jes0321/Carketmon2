#pragma once
enum class Layer
{
	DEFAULT,
	BACKGROUND,
	PLAYER,
	ENEMY,
	CARD,
	UI,
	END
};
enum class PenType
{
	RED, GREEN, YELLOW,BOLD_GREEN,BOLD_GRAY,END
};
enum class BrushType
{
	HOLLOW, RED, GREEN, BLUE,END
};

enum class FontType
{
	UI, TITLE, BIG_UI,BOLD_UI,END
};
enum class ElementType {
	Fire,Water,Ice,Grace
};
enum class CardEffectType {
	Damage,
	Heal,
	StatBuff,
	StatDebuff,
	Buff,
	AoE,
	Shield,
	Focus,
};
enum class CardValueType {
	IntValue,
	MultiplyValue,
	PercentageValue
};
enum class UnitType {
	PLAYER1, PLAYER2, ENEMY,SELF,
};
enum class UIType {
	NONE,
	HAND,
	INFO,
	DECK
};
enum class StatType {
	Attack,
	Defense,
	Speed
};

enum class PlayMode
{
	Once, Loop, Counted
};