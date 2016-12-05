// author: wuming
#pragma once
#include "skill_action_node.h"

class FL_AddBuff:
	public SkillActionNode
{
public:
	FL_AddBuff(std::string name);
	void onBegin()override;
	CC_SYNTHESIZE(std::string, m_strBuffName, BuffName);
	CC_SYNTHESIZE(bool, m_bNeedRollback, NeedRollback);
	void RemoveBuff()override;
protected:
private:
	std::string m_strBuffUUID;
};