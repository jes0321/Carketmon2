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
	RED, GREEN, END
};
enum class BrushType
{
	HOLLOW, RED, GREEN, END
};

enum class FontType
{
	UI, TITLE, END
};
enum class ElementType {
	Fire,Water,Ice,Grace
};
enum class CardEffectType {
	Damage,
	Heal,
	Buff,
	Debuff,
	Utility,
	AoE,
	Shield
};
enum class CardValueType {
	IntValue,
	MultiplyValue,
	PercentageValue
};

enum class PlayMode
{
	Once, Loop, Counted
};