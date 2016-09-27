// author: wuming

#include "skill_selector_node.h"

SkillSelectorNode::SkillSelectorNode(std::string name)
	:BtSelectorNode(name)
{
}

SkillSelectorNode::~SkillSelectorNode()
{
}

void SkillSelectorNode::setBuffOwner(FightPlayer* var)
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

void SkillSelectorNode::setSkillCreator(FightPlayer* var)
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