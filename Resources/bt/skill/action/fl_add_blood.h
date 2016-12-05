// author: wuming
#pragma once
#include "skill_action_node.h"

enum class ESourceType;

class FL_AddBlood:
	SkillActionNode
{
public:
	FL_AddBlood(std::string name);
	void onBegin()override;
	CC_SYNTHESIZE(int, m_nValue, Value);
protected:
private:
};
