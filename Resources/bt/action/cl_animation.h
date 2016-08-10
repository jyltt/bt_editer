#ifndef CL_ANIMATION_H_
#define CL_ANIMATION_H_

#ifdef WIN32
#include "tools/bt/node/actions/bt_action_node.h"
#else
#include "bt_action_node.h"
#endif

#include "cocosfunc/animation/AnimationManager.h"
#include "manager/SceneManager.h"
#include "manager/UIControlManager.h"

// 动画ACT
class CL_Animation :
	public BtActionNode
{
public:
	CL_Animation(std::string name);
	virtual void onBegin();
	virtual EBTState onUpdate()override;
	virtual void Reset();

public:
	inline void setBeginAnimation(const std::string &filename)
	{
		_strAniName = filename;
		AnimationManager::getInstance()->setFrameBeginCallBacker(CC_CALLBACK_0(CL_Animation::onAnimationBegin, this));
		AnimationManager::getInstance()->setFrameEndCallBacker(CC_CALLBACK_0(CL_Animation::onAnimationEnd, this));
	}
	// 事件回调
	virtual void onAnimationBegin();
	virtual void onAnimationEnd();
protected:
private:
	// 动画
	AnimatePlayer *_pAniPlayer{ nullptr };
	std::string _strAniName;
};

#endif