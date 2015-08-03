#include "bt_base_node.h"

BtBaseNode::BtBaseNode(std::string name,EBTNodeType type)
	:m_Name(name)
	, m_curState(EBTState::Inaction)
	, m_NodeType(type)
{

}

void BtBaseNode::onBegin()
{ }

void BtBaseNode::Reset()
{ }

void BtBaseNode::onEnd()
{ }

EBTNodeType BtBaseNode::GetNodeType()
{
	return m_NodeType;
}

BtBaseNode::~BtBaseNode()
{

}