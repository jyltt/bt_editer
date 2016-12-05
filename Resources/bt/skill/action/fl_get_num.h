// author: wuming
#pragma once
#include "skill_action_node.h"

enum class EStorageLocation;
enum class ESourceType;

class FL_GetNum:
	public SkillActionNode
{
public:
	FL_GetNum(std::string name);
	void onBegin()override;
	CC_SYNTHESIZE(EStorageLocation, m_eGetNumPos, GetNumPos);
	CC_SYNTHESIZE(ESourceType, m_eSavePos, SavePos);
	CC_SYNTHESIZE(bool, m_bNeedSuper, NeedSuper);
protected:
private:
};
