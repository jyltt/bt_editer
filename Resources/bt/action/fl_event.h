#ifndef FL_EVENT_H_
#define FL_EVENT_H_

#ifdef WIN32
#include "tools/bt/node/actions/bt_action_node.h"
#else
#include "bt_action_node.h"
#endif

// 事件阶段
class FL_Evnet:
	public BtActionNode
{
public:
	FL_Evnet(std::string name);
	virtual void onBegin()override;
	virtual EBTState onUpdate()override;
protected:
	void onYesCallback();
private:
	bool isOver = false;
};

#endif