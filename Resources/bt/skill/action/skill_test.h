// author: wuming
#ifndef SKILL_TEST_H_
#define SKILL_TEST_H_

#include "skill_action_node.h"

class SkillTest:
	public SkillActionNode
{
public:
	SkillTest(std::string name);
	virtual void onBegin()override;
	virtual EBTState onUpdate()override;
protected:
	void onYesCallback();
	void onNoCallback();
private:
	bool isOver = false;
};

#endif // !SKILL_TEST_H_
