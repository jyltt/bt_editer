#ifndef BT_CONDITION_NODE_H_
#define BT_CONDITION_NODE_H_

#include "bt_base_node.h"

class BtConditionNode:
	public BtBaseNode
{
public:
	BtConditionNode(std::string name);
	virtual~BtConditionNode();
	virtual EBTState onUpdate()override;
	void setCallback(std::function<EBTState()> func);
protected:
	std::function<EBTState()> m_callback;
private:
};
#endif