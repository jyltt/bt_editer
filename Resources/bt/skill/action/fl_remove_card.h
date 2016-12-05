// author: wuming
#pragma once

#include "skill_action_node.h"

enum class ECardAccessType;

class FL_RemoveCard:
	public SkillActionNode
{
public:
	FL_RemoveCard(std::string name);
	virtual void onBegin() override;
	// 从什么地方获取卡牌
	CC_SYNTHESIZE(ECardAccessType, m_eCardAccessType, CardAccessType);
	/* 卡牌序列id
	// 仅用于ECardAccessType为FromStorageBySkill或者FromStorageByBuf时生效
	// 读取buffmanager卡牌序列中 对应位置卡牌
	*/
	CC_SYNTHESIZE(int, m_nIndex, CardIndex);
	/* 指定卡牌id
	// 仅用于ECardAccessType为AssignCard时生效
	*/
	CC_SYNTHESIZE(int, m_nUUID, CardUUID);
protected:
private:
};
