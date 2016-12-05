// author: wuming
#include "fl_change_fight_value.h"
#include "fight_player.h"
#include "buff_manager.h"

FL_ChangeFightValue::FL_ChangeFightValue(std::string name)
	:SkillActionNode(name)
	, m_nFightValue(0)
	, m_bNeedRollback(true)
{
}

void FL_ChangeFightValue::onBegin()
{
	getBuffOwner()->getBuffMgr()->addExFightValue(m_nFightValue);
}

void FL_ChangeFightValue::RemoveBuff()
{
	if (m_bNeedRollback)
	{
		getBuffOwner()->getBuffMgr()->addExFightValue(-m_nFightValue);
	}
}
