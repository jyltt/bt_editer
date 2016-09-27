// author: wuming
#ifndef SKILL_SELECTOR_NODE_H_
#define SKILL_SELECTOR_NODE_H_

#include "bt_selector_node.h"
#include "ex_skill_node.h"


class SkillSelectorNode
	:public BtSelectorNode
	, public ExSkillNode
{
public:
	SkillSelectorNode(std::string name);
	~SkillSelectorNode();
	void setBuffOwner(FightPlayer* var)override;
	void setSkillCreator(FightPlayer* var)override;
protected:
private:
};

#endif