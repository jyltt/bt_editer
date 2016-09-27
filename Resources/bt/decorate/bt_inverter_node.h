// author: wuming
#ifndef BT_INVERTER_H_
#define BT_INVERTER_H_

#include "bt_decorate_node.h"

//È¡·´
class BtInverterNode:
	public BtDecorateNode
{
public:
	BtInverterNode(std::string name)
		:BtDecorateNode(name)
	{ }
	virtual EBTState onUpdate()override
	{
		auto state = m_child->onUpdate();
		switch (state)
		{
		case EBTState::Failed:
			return EBTState::Success;
		case EBTState::Success:
			return EBTState::Failed;
		default:
			return state;
		}
	};
protected:
private:
};

#endif