#ifndef UI_ENUM_H_
#define UI_ENUM_H_

#include <string>

#pragma region 玩家
enum class EPlayerCamp
{
	camp_all,
	camp1,
	camp2,
};
#pragma endregion

#pragma region 人物
enum class EPlayerUpdataType 
{
	all,
	pet,
	hand_card,
	attr,
};
struct PlayerInfo
{
	std::string name;
	bool isDead;
	int humanCard;
};
#pragma endregion

#pragma region 卡牌
enum class CardType //卡牌类型
{
	all,
	hero,
	monster,  // 具体类型详见CardMonsterType 
	hand, // 具体类型详见CardHandType 
};
enum class CardMonsterType // 怪物类型
{
	all,
	npc,
	monster,
};
enum class CardHandType // 手牌类型
{
	all,
	equip,
	skill,
	fight,
	special,
};
struct STR_CardInfo
{
	int uuid;//唯一id
	int id;//卡牌id
	bool isShow; //是否显示卡牌
	CardType type = CardType::all;
};
struct STR_CardMonter
	:public STR_CardInfo
{
	CardMonsterType monsterType = CardMonsterType::all;
};
struct STR_CardHand
	:public STR_CardInfo
{
	CardHandType handType = CardHandType::all;
};
#pragma endregion


#endif