#include "bt_decorate_node.h"

BtDecorateNode::BtDecorateNode(std::string name)
	:BtBaseNode(name,EBTNodeType::Decorate)
{
}

void BtDecorateNode::setChild(BtBaseNode *node)
{
	m_child = node;
}

BtDecorateNode::~BtDecorateNode()
{ }