// author: wuming
#include "skill_test.h"
#include "SceneManager.h"
#include "cocos2d.h"

SkillTest::SkillTest(std::string name)
	:SkillActionNode(name)
{
}

void SkillTest::onBegin()
{
	auto player = getBuffOwner();
	auto creator = getSkillCreator();
	auto root = dynamic_cast<ExSkillNode*>(getBtRoot());
	root->setWait(true);
	SceneManager::getSingleton().GetUIControlMgr().SetShowInfoLab("Running Skill!!!!!!!");
	CCLOG("Running Skill!!!!!!!");
	SceneManager::getSingleton().GetUIControlMgr().ShowDlg("Running Skill!!!!!!!", "技能效果 ", CC_CALLBACK_0(SkillTest::onYesCallback, this), CC_CALLBACK_0(SkillTest::onNoCallback, this));
}

EBTState SkillTest::onUpdate()
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

void SkillTest::onYesCallback()
{
	CCLOG("执行完成");
	isOver = true;
	// 更新行为树状态
	SceneManager::getSingleton().GetProcessMgr().onUpdate();
}

void SkillTest::onNoCallback()
{
	CCLOG("还在执行中 ");
	// 更新行为树状态
	SceneManager::getSingleton().GetProcessMgr().onUpdate();
}