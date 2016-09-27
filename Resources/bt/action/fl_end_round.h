#ifndef FL_END_ROUND_H_
#define FL_END_ROUND_H_

#include "bt_action_node.h"

class FL_EndRound:
	public BtActionNode
{
public:
	FL_EndRound(std::string name);
	virtual EBTState onUpdate()override;
protected:
private:
};

#endif