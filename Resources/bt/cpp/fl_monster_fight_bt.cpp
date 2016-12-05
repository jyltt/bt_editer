// author: wuming
#include "fl_monster_fight_bt.h"
#include "SceneManager.h"
#include "cocos2d.h"

FL_MonsterFightBt::FL_MonsterFightBt(std::string name)
	:BtActionNode(name)
{
}

void FL_MonsterFightBt::onBegin()
{
	SET_FM_TAG("fight_monster", 1);
}

EBTState FL_MonsterFightBt::onUpdate()
{
	BtActionNode::onUpdate();
	return isOver;
}
