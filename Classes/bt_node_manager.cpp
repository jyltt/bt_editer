#include "bt_node_manager.h"

BtNodeManager::BtNodeManager()
:m_RootNode(nullptr)
, m_btNode(nullptr)
{}
BtNodeManager::~BtNodeManager() {}

BtNode *BtNodeManager::CreateNode()
{
	auto node = BtNode::create();
	node->setUUID(id);
	id += 1;
	m_NodeList.push_back(node);
	if (m_RootNode == nullptr)
	{
		m_RootNode = node;
	}
	return node;
}

void BtNodeManager::DeleteNode(BtNode* node)
{
	for (auto it = m_NodeList.begin();it <= m_NodeList.end();it++)
	{
		if ((*it) == node)
		{
			if (m_btNode && node->getUUID() == m_btNode->getUUID())
			{
				setChoseNode(nullptr);
			}
			(*it)->Delete();
			m_NodeList.erase(it);
			break;
		}
	}
}

BtNode* BtNodeManager::TouchNode(Vec2 vec)
{
	for (auto node:m_NodeList)
	{
		if (node->isTouch(vec))
		{
			return node;
		}
	}
	return nullptr;
}

BtNode *BtNodeManager::FindBtNode(int uuid)
{
	for (auto node:m_NodeList)
	{
		if (node->getUUID() == uuid)
		{
			return node;
		}
	}
	return nullptr;
}

void BtNodeManager::onDraw()
{
	for (auto bt:m_NodeList)
	{
		bt->onDraw();
	}
}