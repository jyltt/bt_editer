#include "fl_bt_end.h"
#include "EventManager.h"

void FL_BT_End::onBegin()
{
}

EBTState FL_BT_End::onUpdate()
{
	BtActionNode::onUpdate();
	CCLOG("BT END");

	// 通知process manager切换角色

	return EBTState::Success;
}

void FL_BT_End::onEnd()
{
	// 出发自定义BT结束事件
	EventManager::getInstance()->dispatchCustomEvent("BT_END", nullptr, true);
}
