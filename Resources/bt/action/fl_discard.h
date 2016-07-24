#ifndef FL_DISCARD_H_
#define FL_DISCARD_H_

#ifdef WIN32
#include "tools/bt/node/actions/bt_action_node.h"
#else
#include "bt_action_node.h"
#endif

class FL_Discard:
	public BtActionNode
{
public:
	FL_Discard(std::string name);
	virtual EBTState onUpdate()override;
protected:
private:
};

#endif