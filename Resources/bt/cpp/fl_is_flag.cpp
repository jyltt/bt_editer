//  Created by wuming on 16/3/12.
#include "fl_is_flag.h"

FL_IsFlag::FL_IsFlag(std::string name) :BtConditionNode(name)
{
}

EBTState FL_IsFlag::onUpdate()
{
    BtConditionNode::onUpdate();
    auto value = m_ProcessMgr.getTag(m_Flag);
	EFL_Flag flg = EFL_Flag::Failure;
	if (value != nullptr)
	{
		switch (m_Type)
		{
		case EFlType::int_value:
			flg = value->int_value == m_DefValue.int_value ? EFL_Flag::Success : EFL_Flag::Failure;
			break;
		case EFlType::str:
			flg = value->str == m_DefValue.str ? EFL_Flag::Success : EFL_Flag::Failure;
			break;
		case EFlType::float_value:
			flg = value->float_value == m_DefValue.float_value ? EFL_Flag::Success : EFL_Flag::Failure;
			break;
		}
	}
    m_ProcessMgr.DeleteTag(m_Flag);
    
    switch (flg)
    {
        case EFL_Flag::Failure:
            return EBTState::Failed;
        case EFL_Flag::Success:
            return EBTState::Success;
        default:
            return EBTState::Running;
    }
}

void FL_IsFlag::setDefValue(TagValue var)
{
}
TagValue FL_IsFlag::getDefValue()
{
    return m_DefValue;
}

void FL_IsFlag::setDefValue(int data)
{
    m_DefValue.int_value = data;
    m_Type = EFlType::int_value;
}
void FL_IsFlag::setDefValue(std::string data)
{
    //m_DefValue.str = data;
	data.copy(m_DefValue.str,data.length(),0);
    m_Type = EFlType::str;
}
void FL_IsFlag::setDefValue(float data)
{
    m_DefValue.float_value = data;
    m_Type = EFlType::float_value;
}