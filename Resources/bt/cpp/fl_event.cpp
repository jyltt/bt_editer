#include "fl_event.h"
#include "SceneManager.h"
#include "fight_player.h"
#include "cocos2d.h"

FL_Evnet::FL_Evnet(std::string name)
	:BtActionNode(name)
{ }

void FL_Evnet::onBegin()
{
	//SceneManager::getSingleton().GetUIControlMgr().SetShowInfoLab("Running Event!!!!!!!");
	//CCLOG("Running Event!!!!!!!");
	SceneManager::getSingleton().GetUIControlMgr().ShowDlg("Running Event!!!!!!!", "添加事件牌buff ", CC_CALLBACK_0(FL_Evnet::onYesCallback, this));
	auto eventCard_id = SceneManager::getSingleton().GetFightMgr().GetCardMgr().GetOneEventCard();
	auto eventCard = SceneManager::getSingleton().GetFightMgr().GetCardMgr().FindCard(eventCard_id);
	auto skill_list = eventCard->getActSkill();
	auto cur_player = SceneManager::getSingleton().GetPlayerMgr().GetCurPlayer();
	for (auto skill:skill_list)
		cur_player->AddBuff(skill);
}

EBTState FL_Evnet::onUpdate()
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

void FL_Evnet::onYesCallback()
{
	CCLOG("执行");
	isOver = true;
	// 更新行为树状态
	SceneManager::getSingleton().GetProcessMgr().onUpdate();
}
