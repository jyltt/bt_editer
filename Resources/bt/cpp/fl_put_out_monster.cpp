#include "fl_put_out_monster.h"
#include "SceneManager.h"
#include "cocos2d.h"

FL_PutOutMonster::FL_PutOutMonster(std::string name)
	:BtActionNode(name)
{ }

EBTState FL_PutOutMonster::onUpdate()
{
    BtActionNode::onUpdate();
	SceneManager::getSingleton().GetUIControlMgr().SetShowInfoLab("Running Put Out Monster!!!!!!!");
	CCLOG("Running Put Out Monster!!!!!!!");
	return EBTState::Success;
}