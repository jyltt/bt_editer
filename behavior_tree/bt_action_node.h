#ifndef BT_ACTION_NODE_H_
#define BT_ACTION_NODE_H_

#include "bt_base_node.h"

class BtActionNode:
	public BtBaseNode
{
public:
	BtActionNode(std::string name);
	virtual~BtActionNode();
	virtual EBTState onUpdate() override;
	void setCallback(std::function<EBTState()> func);
protected:
	std::function<EBTState()> m_callback;
private:
};
#endif