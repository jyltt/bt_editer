// author: wuming
#ifndef FL_EVENT_COND_H_
#define FL_EVENT_COND_H_

#include "bt_condition_node.h"

// �¼��׶�
class FL_EvnetCond:
	public BtConditionNode
{
public:
	FL_EvnetCond(std::string name);
	virtual void onBegin()override;
	virtual EBTState onUpdate()override;
protected:
	void onYesCallback();
	void onNoCallback();
private:
	EBTState isOver = EBTState::Running;
};

#endif