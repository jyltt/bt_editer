// author: wuming

#include "skill_sequence_node.h"

SkillSequenceNode::SkillSequenceNode(std::string name)
	:BtSequenceNode(name)
{
}

SkillSequenceNode::~SkillSequenceNode()
{
}

void SkillSequenceNode::setBuffOwner(FightPlayer* var)
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

void SkillSequenceNode::setSkillCreator(FightPlayer* var)
{
	m_skillCreator = var;
	for (auto node:m_Childs)
	{
		auto bt = dynamic_cast<ExSkillNode*>(node);
		if (bt)
		{
			bt->setSkillCreator(var);
		}
	}
}
