#include "bt_composite_node.h"

BtCompositeNode::BtCompositeNode(std::string name,EBTNodeType type)
	:BtBaseNode(name,type)
	,m_curNodeCnt(0)
	, m_AbortType(EBTAbortType::none)
{

}

bool BtCompositeNode::AddChild(BtBaseNode *child)
{
	m_Childs.push_back(child);
	return true;
}

bool BtCompositeNode::RemoveChild(BtBaseNode *child)
{
	for (auto it = m_Childs.begin(); it != m_Childs.end(); it++)
	{
		if (*it == child)
		{
			m_Childs.erase(it);
			return true;
		}
	}
	return false;
}

int BtCompositeNode::Abort()
{
	int i;
	switch (m_curState)
	{
	case EBTState::Inaction:
		i = 0;
		break;
	case EBTState::Failed:
	case EBTState::Success:
		if (getAbortType() == EBTAbortType::both
			|| getAbortType() == EBTAbortType::priority)
			i = 0;
		else
			i = -1;
		break;
	case EBTState::Running:
		if (getAbortType() == EBTAbortType::both
			|| getAbortType() == EBTAbortType::self
			|| getAbortType() == EBTAbortType::none)
			i = 0;
		else
			i = m_curNodeCnt;
		break;
	default:
		break;
	}
	return i;
}

void BtCompositeNode::Reset()
{
	m_curNodeCnt = 0;
	for (auto it:m_Childs)
	{
		it->Reset();
	}
}

BtCompositeNode::~BtCompositeNode()
{

}