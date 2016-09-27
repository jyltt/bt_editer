// author: wuming
#ifndef SKILL_PARALLEL_NODE_H_
#define SKILL_PARALLEL_NODE_H_

#include "bt_parallel_node.h"
#include "ex_skill_node.h"


class SkillParallelNode
	:public BtParallelNode
	, public ExSkillNode
{
public:
	SkillParallelNode(std::string name);
	~SkillParallelNode();
	void setBuffOwner(FightPlayer* var)override;
	void setSkillCreator(FightPlayer* var)override;
protected:
private:
};

#endif