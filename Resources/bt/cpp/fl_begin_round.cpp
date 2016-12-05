#include "fl_begin_round.h"
#include "SceneManager.h"
#include "cocos2d.h"

FL_BeginRound::FL_BeginRound(std::string name)
	:BtActionNode(name)
{ }

void FL_BeginRound::onBegin()
{
	SceneManager::getSingleton().GetUIControlMgr().SetShowInfoLab("Running Begin Round!!!!!!!");
	CCLOG("Running Begin Round!!!!!!!");
	SceneManager::getSingleton().GetUIControlMgr().ShowDlg("Running Begin Round!!!!!!!", "这里可以执行一些动画什么的", CC_CALLBACK_0(FL_BeginRound::onYesCallback, this));
}

EBTState FL_BeginRound::onUpdate()
{
    BtActionNode::onUpdate();
	if (isOver)
	{
		return EBTState::Success;
	}
	else
	{
		return EBTState::Running;
	}
}

void FL_BeginRound::onEnd()
{
	// skillCreator把buff添加到player1身上
	//auto skillCreator = SceneManager::getSingleton().GetPlayerMgr().FindPlayer(1);
	//auto card = SceneManager::getSingleton().GetFightMgr().GetCardMgr().GetOneEventCard();
	//auto buffs = card->getActSkill();
	//for (auto buff:buffs)
	//{
	//	//buff->setSkillCreator(skillCreator);
	//	auto player1 = SceneManager::getSingleton().GetPlayerMgr().FindPlayer(0);
	//	player1->AddBuff(buff);
	//}
}

void FL_BeginRound::onYesCallback()
{
	CCLOG("执行完成");
	isOver = true;
	// 更新行为树状态
	SceneManager::getSingleton().GetProcessMgr().onUpdate();
}
