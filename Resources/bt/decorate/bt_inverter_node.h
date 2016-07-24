// author: wuming
#ifndef BT_INVERTER_H_
#define BT_INVERTER_H_

#if WIN32
#include "tools/bt/node/base/bt_decorate_node.h"
#else
#include "bt_decorate_node.h"
#endif

//È¡·´
class BtInverterNode:
	public BtDecorateNode
{
public:
	BtInverterNode(std::string name);
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