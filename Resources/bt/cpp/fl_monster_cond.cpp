// author: wuming
#include "fl_monster_cond.h"
#include "SceneManager.h"
#include "cocos2d.h"

FL_MonsterCond::FL_MonsterCond(std::string name)
	:BtConditionNode(name)
{
}

void FL_MonsterCond::onBegin()
{
	isOver = EBTState::Running;
	SceneManager::getSingleton().GetUIControlMgr().SetShowInfoLab("chose Monster!!!!!!!");
	CCLOG("Running Event!!!!!!!");
	SceneManager::getSingleton().GetUIControlMgr().ShowDlg("chose Monster!!!!!!!", "�Ƿ��� ", CC_CALLBACK_0(FL_MonsterCond::onNoCallback, this));
}

EBTState FL_MonsterCond::onUpdate()
{
	BtConditionNode::onUpdate();
	return isOver;
}

void FL_MonsterCond::onYesCallback()
{
	CCLOG("ִ�� ");
	isOver = EBTState::Success;
	// ������Ϊ��״̬
	SceneManager::getSingleton().GetProcessMgr().onUpdate();
}

void FL_MonsterCond::onNoCallback()
{
	CCLOG("��ִ�� ");
	isOver = EBTState::Failed;
	// ������Ϊ��״̬
	SceneManager::getSingleton().GetProcessMgr().onUpdate();
}
