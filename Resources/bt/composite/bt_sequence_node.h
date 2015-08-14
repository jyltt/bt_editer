#ifndef BT_SEQUENCE_NODE
#define BT_SEQUENCE_NODE

#include "bt_composite_node.h"

class BtSequenceNode:
	public BtCompositeNode
{
public:
	BtSequenceNode(std::string name);
	~BtSequenceNode();
	virtual EBTState onUpdate() override;
private:
};

#endif