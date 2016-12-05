// author: wuming
#ifndef FL_CHOOSE_PLAYER_H_
#define FL_CHOOSE_PLAYER_H_

#include "skill_action_node.h"

class Card;
enum class EChosePerson;

class FL_ChoosePlayer:
	public SkillActionNode
{
public:
	FL_ChoosePlayer(std::string name);
	virtual void onBegin() override;
	EBTState onUpdate()override;
	/**
	//  是否需要清除之前存储的数据
	**/
	CC_SYNTHESIZE(bool, m_bNeedClearTarget, NeedClearTArget);
	/** 
	//  选择对象类型
	//  敌方
	//  己方
	//  妨碍者
	//  支援者
	//  自己
	//  所有人
	//  血量最少
	**/
	CC_SYNTHESIZE(EChosePerson, m_eChosePerson, ChosePerson);
	/**
	//  是否可主动选择
	**/
	CC_SYNTHESIZE(bool, m_bNeedPlayer, NeedPlayer);
protected:
	void on_choose(Card* card, void* param);
private:
	bool m_isChose=false;

};

#endif
