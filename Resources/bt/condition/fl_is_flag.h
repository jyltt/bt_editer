#ifndef FL_IS_FLAG_H_
#define FL_IS_FLAG_H_

#ifdef WIN32
#include "tools/bt/node/actions/bt_condition_node.h"
#include "manager/SceneManager.h"
#else
#include "bt_condition_node.h"
#include "SceneManager.h"
#endif
#include "cocos2d.h"


class FL_IsFlag:
	public BtConditionNode
{
protected:
    enum class EFlType
    {
        str,
        int_value,
        float_value,
    };
public:
    FL_IsFlag(std::string name);
    virtual EBTState onUpdate()override;
	
	CC_SYNTHESIZE(std::string, m_Flag, Flag);
	CC_SYNTHESIZE(EFlType, m_Type, Type);
    CC_PROPERTY(TagValue,m_DefValue,DefValue);
    void setDefValue(int data);
    void setDefValue(std::string data);
    void setDefValue(float data);
private:
    ProcessManager &m_ProcessMgr = SceneManager::getSingleton().GetProcessMgr();
};

#endif