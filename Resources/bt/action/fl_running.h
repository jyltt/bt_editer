#ifndef FL_RUNNING_H_
#define FL_RUNNING_H_

#include "bt_action_node.h"
#include "cocos2d.h"

class FL_Running:
	public BtActionNode
{
public:
	FL_Running(std::string name) :BtActionNode(name)
	{ }
	virtual EBTState onUpdate()override
	{
        BtActionNode::onUpdate();
		CCLOG("Running");
		return EBTState::Running;
	}
protected:
private:
};

#endif
