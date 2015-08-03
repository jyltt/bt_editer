#include "bt_parallel_node.h"

BtParallelNode::BtParallelNode(std::string name)
	:BtCompositeNode(name,EBTNodeType::Parallel)
{

}

EBTState BtParallelNode::onUpdate()
{
	int i = Abort();
	if (i < 0)
		return EBTState::Failed;
	for (; i<m_Childs.size(); i++)
	{
		{
			if (i != m_curNodeCnt&&getCurState()!=EBTState::Running)
				m_Childs[i]->onBegin();
			m_curState = m_Childs[i]->onUpdate();
			switch (m_curState)
			{
			case EBTState::Failed:
				break;
			case EBTState::Success:
				break;
			case EBTState::Running:
				m_curNodeCnt = i;
				return EBTState::Running;
			default:
				cocos2d::log("error£º ´íÎóµÄ±ê¼Ç name:%s", m_Name);
				break;
			}
			m_Childs[i]->onEnd();
		}
	}
	m_curNodeCnt = 0;
	return EBTState::Success;
}

BtParallelNode::~BtParallelNode()
{
}