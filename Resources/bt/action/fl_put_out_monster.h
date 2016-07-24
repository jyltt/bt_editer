#ifndef FL_PUT_OUT_MONSTER_H_
#define FL_PUT_OUT_MONSTER_H_

#ifdef WIN32
#include "tools/bt/node/actions/bt_action_node.h"
#else
#include "bt_action_node.h"
#endif

class FL_PutOutMonster:
	public BtActionNode
{
public:
	FL_PutOutMonster(std::string name);
	virtual EBTState onUpdate()override;
protected:
private:
};

#endif