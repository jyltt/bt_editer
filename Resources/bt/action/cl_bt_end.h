#ifndef FL_BT_END_H_
#define FL_BT_END_H_

#ifdef WIN32
#include "tools/bt/node/actions/bt_action_node.h"
#else
#include "bt_action_node.h"
#endif
#include "cocos2d.h"

// BTÁ÷³Ì½áÊøACT
class FL_BT_End :
	public BtActionNode
{
public:
	FL_BT_End(std::string name) :BtActionNode(name)
	{ }

public:
	virtual void onBegin()override;
	virtual EBTState onUpdate()override;
	virtual void onEnd()override;

protected:
private:
};

#endif
