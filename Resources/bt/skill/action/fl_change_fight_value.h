// author: wuming
#pragma once

#include "skill_action_node.h"

class FL_ChangeFightValue:
	public SkillActionNode
{
public:
	FL_ChangeFightValue(std::string name);
	virtual void onBegin() override;
	CC_SYNTHESIZE(int, m_nFightValue, ChangeFightValue);
	CC_SYNTHESIZE(bool, m_bNeedRollback, NeedRollback);
	virtual void RemoveBuff()override;
protected:
private:
};
