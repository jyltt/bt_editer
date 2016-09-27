// author: wuming
#ifndef FL_MONSTER_FIGHT_BT_H_
#define FL_MONSTER_FIGHT_BT_H_

#include "bt_action_node.h"

// ÊÂ¼þ½×¶Î
class FL_MonsterFightBt:
	public BtActionNode
{
public:
	FL_MonsterFightBt(std::string name);
	virtual void onBegin()override;
	virtual EBTState onUpdate()override;
protected:
private:
	EBTState isOver = EBTState::Running;
};

#endif