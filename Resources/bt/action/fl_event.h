#ifndef FL_EVENT_H_
#define FL_EVENT_H_

#include "bt_action_node.h"

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