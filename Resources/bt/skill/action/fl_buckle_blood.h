// author: wuming
#pragma once
#include "skill_action_node.h"

enum class ESourceType;

class FL_BuckleBlood:
	SkillActionNode
{
public:
	FL_BuckleBlood(std::string name);
	void onBegin()override;
	CC_SYNTHESIZE(int, m_nValue, Value);
protected:
private:
};
