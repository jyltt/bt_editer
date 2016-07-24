// author: wuming
#ifndef FL_IS_TRUE_H_
#define FL_IS_TRUE_H_

#ifdef WIN32
#include "tools/bt/node/actions/bt_condition_node.h"
#else
#include "bt_condition_node.h"
#endif


class FL_IsTrue :
	public BtConditionNode
{
protected:
public:
	FL_IsTrue(std::string name) :BtConditionNode(name) {};
	virtual EBTState onUpdate()override
	{
		return EBTState::Success;
	};
private:
};

#endif