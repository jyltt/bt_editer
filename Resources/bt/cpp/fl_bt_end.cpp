#include "fl_bt_end.h"
#include "EventManager.h"

void FL_BT_End::onBegin()
{
}

EBTState FL_BT_End::onUpdate()
{
	BtActionNode::onUpdate();
	CCLOG("BT END");

	// ֪ͨprocess manager�л���ɫ

	return EBTState::Success;
}

void FL_BT_End::onEnd()
{
	// �����Զ���BT�����¼�
	EventManager::getInstance()->dispatchCustomEvent("BT_END", nullptr, true);
}
