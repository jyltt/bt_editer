// author: wuming
#include "fl_buckle_blood.h"
#include "fight_player.h"

FL_BuckleBlood::FL_BuckleBlood(std::string name)
	:SkillActionNode(name)
	, m_nValue(0)
{

}

void FL_BuckleBlood::onBegin()
{
	auto player = getBuffOwner();
	CC_ASSERT(m_nValue > 0);
	if (m_nValue <= 0)
	{
		player->ChangeHp(m_nValue);
	}
}
