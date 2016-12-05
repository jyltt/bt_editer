// author: wuming
#include "fl_calc.h"
#include "fight_event_enum.h"
#include "fight_player.h"
#include "buff_manager.h"

FL_Calc::FL_Calc(std::string name)
	:SkillActionNode(name)
	, m_eType(ECalcType::Add)
	, m_eSourceType(ESourceType::BuffOwer)
{
}

void FL_Calc::onBegin()
{
	int num = 0;
	BuffManager* buffMgr = nullptr;
	switch (m_eSourceType)
	{
	case ESourceType::BuffOwer:
		buffMgr = getBuffOwner()->getBuffMgr();
		break;
	case ESourceType::SkillCreator:
		buffMgr = getSkillCreator()->getBuffMgr();
		break;
	default:
		break;
	}
	CC_ASSERT(buffMgr!=nullptr);
	num = buffMgr->getSaveNum();

	switch (m_eType)
	{
	case ECalcType::Add:
		num += m_nValue;
		break;
	case ECalcType::Sub:
		num -= m_nValue;
		break;
	case ECalcType::Mul:
		num *= m_nValue;
		break;
	case ECalcType::Div:
		num /= m_nValue;
		break;
	default:
		break;
	}

	buffMgr->setSaveNum(num);
}
