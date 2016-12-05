// author: wuming
#pragma once

#include "skill_action_node.h"

class FL_ExReply:
	public SkillActionNode
{
public:
	FL_ExReply(std::string name);
	virtual void onBegin() override;
	CC_SYNTHESIZE(int, m_nExReply, ExReply);
	CC_SYNTHESIZE(bool, m_bNeedRollback, NeedRollback);
	virtual void RemoveBuff()override;
protected:
private:
};