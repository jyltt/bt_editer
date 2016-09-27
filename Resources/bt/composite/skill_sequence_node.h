// author: wuming
#ifndef SKILL_SEQUENCE_NODE_H_
#define SKILL_SEQUENCE_NODE_H_

#include "bt_sequence_node.h"
#include "ex_skill_node.h"


class SkillSequenceNode
	:public BtSequenceNode
	, public ExSkillNode
{
public:
	SkillSequenceNode(std::string name);
	~SkillSequenceNode();
	void setBuffOwner(FightPlayer* var)override;
	void setSkillCreator(FightPlayer* var)override;
protected:
private:
};

#endif