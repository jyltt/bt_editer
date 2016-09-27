// author: wuming
#ifndef FL_GET_HANDCARD_H_
#define FL_GET_HANDCARD_H_

#include "skill_action_node.h"

class FL_GetHandcard :
	public SkillActionNode 
{
public:
	FL_GetHandcard(std::string name);
	virtual void onBegin() override;
protected:
private:
};

#endif