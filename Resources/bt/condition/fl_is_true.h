// author: wuming
#ifndef FL_IS_TRUE_H_
#define FL_IS_TRUE_H_

#include "bt_condition_node.h"

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