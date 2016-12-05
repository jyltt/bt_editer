// author: wuming
#include "fl_ex_reply.h"
#include "fight_player.h"
#include "buff_manager.h"

FL_ExReply::FL_ExReply(std::string name)
	:SkillActionNode(name)
	, m_bNeedRollback(true)
	, m_nExReply(0)
{
}

void FL_ExReply::onBegin()
{
	getBuffOwner()->getBuffMgr()->addExReply(m_nExReply);
}

void FL_ExReply::RemoveBuff()
{
	if (m_bNeedRollback)
	{
		getBuffOwner()->getBuffMgr()->addExReply(-m_nExReply);
	}
}
