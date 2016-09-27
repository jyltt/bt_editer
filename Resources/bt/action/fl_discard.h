#ifndef FL_DISCARD_H_
#define FL_DISCARD_H_

#include "bt_action_node.h"

class FL_Discard:
	public BtActionNode
{
public:
	FL_Discard(std::string name);
	virtual void onBegin()override;
	virtual EBTState onUpdate()override;
protected:
private:
};

#endif