#ifndef BT_PARALLEL_NODE_H_
#define BT_PARALLEL_NODE_H_

#include "bt_composite_node.h"

class BtParallelNode:
	public BtCompositeNode
{
public:
	BtParallelNode(std::string name);
	~BtParallelNode();
	virtual EBTState onUpdate() override;
protected:

};

#endif