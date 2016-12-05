// author: wuming
#pragma once
#include "skill_action_node.h"

enum class ECalcType;
enum class ESourceType;

class FL_Calc
	:SkillActionNode
{
public:
	FL_Calc(std::string name);
	void onBegin()override;
	CC_SYNTHESIZE(ECalcType, m_eType, CalcType);
	CC_SYNTHESIZE(ESourceType, m_eSourceType, SourceType);
	CC_SYNTHESIZE(int, m_nValue, Value);
protected:
private:
};