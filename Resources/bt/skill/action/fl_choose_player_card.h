// author: wuming
#ifndef FL_CHOOSE_PLAYER_CARD_H_
#define FL_CHOOSE_PLAYER_CARD_H_

#include "skill_action_node.h"

class Card;
enum class EStorageLocation;
enum class ESourceType;

class FL_ChoosePlayerCard :
	public SkillActionNode
{
public:
	FL_ChoosePlayerCard(std::string name);
	virtual void onBegin() override;
	EBTState onUpdate()override;
	/**
	//  是否可主动选择
	**/
	CC_SYNTHESIZE(bool, m_bNeedPlayer, NeedPlayer);
	/** 
	//  选择位置
	**/
	CC_SYNTHESIZE(EStorageLocation, m_eCardType, CardType);
	/**
	//  对象玩家提取位置
	**/
	CC_SYNTHESIZE(ESourceType, m_eSourceType, SourceType);
	/** 
	//  保存数据位置
	**/
	CC_SYNTHESIZE(ESourceType, m_eSavePos, SavePos);
protected:
	void on_choose(Card* card, void* param);
	void SaveInfo(int uuid);
private:
	bool m_isChose = false;

};

#endif
