#include "bt_action_node.h"

BtActionNode::BtActionNode(std::string name)
	:BtBaseNode(name,EBTNodeType::Action)
	,m_callback(nullptr)
{
	
}

EBTState BtActionNode::onUpdate()
{
	if (m_callback)
	{
		return m_callback();
	}
	return EBTState::Success;
}

void BtActionNode::setCallback(std::function<EBTState()> func)
{
	m_callback = func;
}

BtActionNode::~BtActionNode()
{

}