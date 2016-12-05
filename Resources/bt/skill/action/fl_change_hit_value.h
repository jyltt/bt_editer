// author: wuming
#pragma once

#include "skill_action_node.h"

class FL_ChangeHitValue :
	public SkillActionNode
{
public:
	FL_ChangeHitValue(std::string name);
	virtual void onBegin() override;
	CC_SYNTHESIZE(int, m_nHitValue, ChangeHitValue);
	CC_SYNTHESIZE(bool, m_bNeedRollback, NeedRollback);
	virtual void RemoveBuff()override;
protected:
private:
};
