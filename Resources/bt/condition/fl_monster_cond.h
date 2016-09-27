// author: wuming
#ifndef FL_MONSTER_COND_H_
#define FL_MONSTER_COND_H_

#include "bt_condition_node.h"

// �¼��׶�
class FL_MonsterCond:
	public BtConditionNode
{
public:
	FL_MonsterCond(std::string name);
	virtual void onBegin()override;
	virtual EBTState onUpdate()override;
protected:
	void onYesCallback();
	void onNoCallback();
private:
	EBTState isOver = EBTState::Running;
};

#endif