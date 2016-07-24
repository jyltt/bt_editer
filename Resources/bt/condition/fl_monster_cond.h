// author: wuming
#ifndef FL_MONSTER_COND_H_
#define FL_MONSTER_COND_H_

#ifdef WIN32
#include "tools/bt/node/actions/bt_condition_node.h"
#else
#include "bt_condition_node.h"
#endif

// ÊÂ¼þ½×¶Î
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