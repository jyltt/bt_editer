// author: wuming
#ifndef FL_ANIMATION_H_
#define FL_ANIMATION_H_

#include "bt_action_node.h"
#include "SceneManager.h"
#include "UIControlManager.h"
#include "cocostudio/CocoStudio.h"

// ¶¯»­ACT
class FL_Animation :
	public BtActionNode
{
public:
	FL_Animation(std::string name);
	virtual void onBegin()override;
	virtual EBTState onUpdate()override;
	virtual void onEnd()override;
	virtual void Reset()override;

	void setAnimName(const std::string &filename);
	virtual void onFrameEvent(cocostudio::timeline::Frame* frame);
	virtual void onFrameBegin();
	virtual void onFrameEnd();
protected:
	void createAnim();
	void playerAnim();
	virtual void initAnim() {};
private:
	// ¶¯»­
	Node* m_pAniPlayer = nullptr;
	cocostudio::timeline::ActionTimeline *m_timeLine;
	std::string m_strAniName;
};

#endif