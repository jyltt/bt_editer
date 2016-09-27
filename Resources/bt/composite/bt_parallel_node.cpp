#include "bt_parallel_node.h"

BtParallelNode::BtParallelNode(std::string name)
	:BtCompositeNode(name,EBTNodeType::Parallel)
{

}

EBTState BtParallelNode::onUpdate()
{
    BtCompositeNode::onUpdate();
	int i = Abort();
	if (i < 0)
		return m_curState;
	for (; i<m_Childs.size(); i++)
	{
		auto node = m_Childs[i];
		auto type = node->GetNodeType();
		auto curState = updateNode(node,i);

		switch (curState)
		{
		case EBTState::Failed:
			break;
		case EBTState::Success:
			if (type == EBTNodeType::Condition)
			{
				for (int j = i+1; j<m_Childs.size(); ++j)
					m_Childs[j]->Reset();
			}
			break;
		case EBTState::Running:
			m_curNodeCnt = i;
			return EBTState::Running;
		default:
			cocos2d::log("error: error tag name:%s", m_Name.c_str());
			break;
		}
		node->onEnd();
	}
	m_curNodeCnt = -1;
	return EBTState::Success;
}

BtParallelNode::~BtParallelNode()
{
}