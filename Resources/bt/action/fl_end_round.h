#ifndef FL_END_ROUND_H_
#define FL_END_ROUND_H_

#ifdef WIN32
#include "tools/bt/node/actions/bt_action_node.h"
#else
#include "bt_action_node.h"
#endif

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