#ifndef BT_SELECT_NODE_H_
#define BT_SELECT_NODE_H_

#include "bt_composite_node.h"

class BtSelectorNode:
	public BtCompositeNode
{
public:
	BtSelectorNode(std::string name);
	~BtSelectorNode();
	virtual EBTState onUpdate() override;
private:
};
#endif