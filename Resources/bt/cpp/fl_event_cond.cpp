// author: wuming
#include "fl_event_cond.h"
#include "SceneManager.h"
#include "cocos2d.h"

FL_EvnetCond::FL_EvnetCond(std::string name)
	:BtConditionNode(name)
{
}

void FL_EvnetCond::onBegin()
{
	isOver = EBTState::Running;
	SceneManager::getSingleton().GetUIControlMgr().SetShowInfoLab("Running Event!!!!!!!");
	CCLOG("Running Event!!!!!!!");
	SceneManager::getSingleton().GetUIControlMgr().ShowDlg("Running Event!!!!!!!", "是否执行事件牌效果 ", CC_CALLBACK_0(FL_EvnetCond::onYesCallback, this), CC_CALLBACK_0(FL_EvnetCond::onNoCallback, this));
}

EBTState FL_EvnetCond::onUpdate()
{
	BtConditionNode::onUpdate();
	return isOver;
}

void FL_EvnetCond::onYesCallback()
{
	CCLOG("执行 ");
	isOver = EBTState::Success;
	// 更新行为树状态
	SceneManager::getSingleton().GetProcessMgr().onUpdate();
}

void FL_EvnetCond::onNoCallback()
{
	CCLOG("不执行 ");
	isOver = EBTState::Failed;
	// 更新行为树状态
	SceneManager::getSingleton().GetProcessMgr().onUpdate();
}
