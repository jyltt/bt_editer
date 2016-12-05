// author: wuming
#include "fl_animation.h"
#include "SceneManager.h"
#include "cocos2d.h"
using namespace cocostudio::timeline;

FL_Animation::FL_Animation(std::string name)
	:BtActionNode(name)
{
}

void FL_Animation::onBegin()
{
	BtActionNode::onBegin();
	createAnim();
	playerAnim();
}

EBTState FL_Animation::onUpdate()
{
	BtActionNode::onUpdate();
	SceneManager::getSingleton().GetUIControlMgr().SetShowInfoLab("Running Animation!!!!!!!");
	CCLOG("Running Animation!!!!!!!");
	return m_timeLine->isPlaying() ? EBTState::Running : EBTState::Success;
}

void FL_Animation::onEnd()
{
	if (m_timeLine->isPlaying())
	{
		SceneManager::getSingleton().GetUIControlMgr().RemoveAnimation(m_pAniPlayer);
	}
}

void FL_Animation::setAnimName(const std::string &filename)
{
	m_strAniName = filename;
}

void FL_Animation::Reset()
{
	BtBaseNode::Reset();
	//m_pAniPlayer->stop();
}

void FL_Animation::createAnim()
{
	if (!m_strAniName.empty())
	{
		m_timeLine = CSLoader::createTimeline(m_strAniName);
		m_timeLine->setFrameEventCallFunc(CC_CALLBACK_1(FL_Animation::onFrameEvent, this));
		m_timeLine->addFrameEndCallFunc(1, "onFrameBegin", CC_CALLBACK_0(FL_Animation::onFrameBegin, this));
		m_timeLine->setLastFrameCallFunc(CC_CALLBACK_0(FL_Animation::onFrameEnd, this));
		m_pAniPlayer = CSLoader::createNode(m_strAniName);
		m_pAniPlayer->runAction(m_timeLine);
		initAnim();
	}
}

void FL_Animation::playerAnim()
{
	SceneManager::getSingleton().GetUIControlMgr().AddAnimation(m_pAniPlayer);
	m_timeLine->gotoFrameAndPlay(0, false);
}

void FL_Animation::onFrameEvent(Frame* frame)
{
	EventFrame* evnt = dynamic_cast<EventFrame*>(frame);
	if (!evnt)
	{
		return;
	}

}
void FL_Animation::onFrameBegin()
{
	log("animation running");
}
void FL_Animation::onFrameEnd()
{
	log("animation end");
}
