#include "bt_selector_node.h"

BtSelectorNode::BtSelectorNode(std::string name)
	:BtCompositeNode(name,EBTNodeType::Selector)
{

}

EBTState BtSelectorNode::onUpdate()
{
    BtCompositeNode::onUpdate();
	int i = Abort();
	if (i < 0)
		return m_curState;
	for (; i<m_Childs.size();i++)
	{
		auto node = m_Childs[i];
		auto type = node->GetNodeType();
		auto curState = updateNode(node,i);
		
		switch (curState)
		{
		case EBTState::Failed:
			break;
		case EBTState::Success:
			m_curNodeCnt = 0;
			m_Childs[i]->onEnd();
			return EBTState::Success;
		case EBTState::Running:
			m_curNodeCnt = i;
			return EBTState::Running;
		default:
			cocos2d::log("error: error tag name:%s",m_Name.c_str());
			break;
		}
		m_Childs[i]->onEnd();
	}
	m_curNodeCnt = 0;
	return EBTState::Failed;
}

BtSelectorNode::~BtSelectorNode()
{

}