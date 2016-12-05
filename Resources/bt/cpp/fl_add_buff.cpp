// author: wuming
#include "fl_add_buff.h"
#include "bt_list.h"
#include "fight_player.h"

FL_AddBuff::FL_AddBuff(std::string name)
	:SkillActionNode(name)
	, m_bNeedRollback(true)
{

}

void FL_AddBuff::onBegin()
{
	if (m_strBuffName.empty())
		return;
	auto player = getBuffOwner();
	auto buff = BTList::getSingleton().CreateSkill(m_strBuffName);
	m_strBuffUUID = buff->getUUID();
	player->AddBuff(buff);
}

void FL_AddBuff::RemoveBuff()
{
	if (!m_bNeedRollback)
		return;
	CC_ASSERT(m_strBuffUUID.empty());
	auto player = getBuffOwner();
	player->RemoveBuff(m_strBuffUUID);
}
