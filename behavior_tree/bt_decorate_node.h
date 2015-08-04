#ifndef BT_DECORATE_NODE_H_
#define BT_DECORATE_NODE_H_

#include "bt_base_node.h"

class BtDecorateNode:
	public BtBaseNode
{
public:
	BtDecorateNode(std::string name);
	virtual ~BtDecorateNode();
	void setChild(BtBaseNode *node);
protected:
	BtBaseNode *m_child=nullptr;
private:
};
#endif