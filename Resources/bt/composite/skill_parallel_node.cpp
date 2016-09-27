// author: wuming

#include "skill_parallel_node.h"

SkillParallelNode::SkillParallelNode(std::string name)
	:BtParallelNode(name)
{
}

SkillParallelNode::~SkillParallelNode()
{
}

void SkillParallelNode::setBuffOwner(FightPlayer* var)
{
	m_buffOwner = var;
	for (auto node:m_Childs)
	{
		auto bt = dynamic_cast<ExSkillNode*>(node);
		if (bt)
		{
			bt->setBuffOwner(var);
		}
	}
}

void SkillParallelNode::setSkillCreator(FightPlayer* var)
{
	m_buffOwner = var;
	for (auto node:m_Childs)
	{
		auto bt = dynamic_cast<ExSkillNode*>(node);
		if (bt)
		{
			bt->setSkillCreator(var);
		}
	}
}
