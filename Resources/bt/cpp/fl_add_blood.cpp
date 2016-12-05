// author: wuming
#include "fl_add_blood.h"
#include "fight_player.h"

FL_AddBlood::FL_AddBlood(std::string name)
	:SkillActionNode(name)
	, m_nValue(0)
{

}

void FL_AddBlood::onBegin()
{
	auto player = getBuffOwner();
	CC_ASSERT(m_nValue < 0);
	if (m_nValue >= 0)
	{
		player->ChangeHp(m_nValue);
	}
}
