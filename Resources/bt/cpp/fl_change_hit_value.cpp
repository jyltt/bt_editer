// author: wuming
#include "fl_change_hit_value.h"
#include "fight_player.h"
#include "buff_manager.h"

FL_ChangeHitValue::FL_ChangeHitValue(std::string name)
	:SkillActionNode(name)
	, m_nHitValue(0)
	, m_bNeedRollback(true)
{
}

void FL_ChangeHitValue::onBegin()
{
	getBuffOwner()->getBuffMgr()->addExHitValue(m_nHitValue);
}

void FL_ChangeHitValue::RemoveBuff()
{
	if (m_bNeedRollback)
	{
		getBuffOwner()->getBuffMgr()->addExHitValue(-m_nHitValue);
	}
}
