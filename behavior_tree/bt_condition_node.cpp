#include "bt_condition_node.h"

BtConditionNode::BtConditionNode(std::string name)
	:BtBaseNode(name,EBTNodeType::Condition)
	,m_callback(nullptr)
{

}

EBTState BtConditionNode::onUpdate()
{
	if (m_callback)
	{
		return m_callback();
	}
	return EBTState::Success;
}

void BtConditionNode::setCallback(std::function<EBTState()> func)
{
	m_callback = func;
}

BtConditionNode::~BtConditionNode()
{

}