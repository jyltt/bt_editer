// author: wuming
#ifndef FL_MONSTER_FIGHT_BT_H_
#define FL_MONSTER_FIGHT_BT_H_

#ifdef WIN32
#include "tools/bt/node/actions/bt_action_node.h"
#else
#include "bt_action_node.h"
#endif

// �¼��׶�
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