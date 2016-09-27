#ifndef FL_PUT_OUT_MONSTER_H_
#define FL_PUT_OUT_MONSTER_H_

#include "bt_action_node.h"

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