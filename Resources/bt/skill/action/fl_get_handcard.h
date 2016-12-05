// author: wuming
#ifndef FL_GET_HANDCARD_H_
#define FL_GET_HANDCARD_H_

#include "skill_action_node.h"

enum class ECardAccessType;
enum class EStorageLocation;

class FL_GetHandcard :
	public SkillActionNode 
{
public:
	FL_GetHandcard(std::string name);
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
	// 将卡牌存放在玩家什么地方
	CC_SYNTHESIZE(EStorageLocation, m_eStorageLocation, StorageLocation);
	virtual void onBegin() override;
protected:
private:
};

#endif
