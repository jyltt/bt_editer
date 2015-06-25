#include "bt_node_manager.h"

BtNodeManager::BtNodeManager()
:m_RootNode(nullptr)
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

std::string BtNodeManager::WriteFile()
{
	if (m_RootNode == nullptr)
		return "m_RootNode is nullptr!";
	auto name = m_RootNode->getClassName();
	if (name == "")
		return "m_RootNode class name is nullptr!";
	auto type = GetEnumToString(m_RootNode->getNodeType());
	if (type == "")
		return "m_RootNode type is nullptr!";
	char buff[300];
	sprintf(buff, "auto %s = BT_Factory::Create(EBTNode::%s, \"%s\");\nm_root = %s;\n", name.c_str(), type.c_str(), name.c_str(), name.c_str());
	m_FileBuff = buff;
	for (int i = 0; i < m_RootNode->m_ChildNode.size(); i++)
	{
		std::string ret = "successs!!!";
		ret = GetChild(m_RootNode, m_RootNode->m_ChildNode[i]);
		if (ret != "successs!!!")
			return ret;
	}

	FILE *fp = fopen("bt_tree.txt", "wb");
	if (fp)
	{
		fwrite(m_FileBuff.c_str(), 1, strlen(m_FileBuff.c_str()), fp);
		fclose(fp);
		return "Write succeed";
	}
	else
		return "Write failed";

}

std::string BtNodeManager::GetEnumToString(BtNode::NodeType type)
{
	std::string type_str = "";
	switch (type)
	{
	case BtNode::NodeType::Sequence:
		type_str = "Sequence";
		break;
	case BtNode::NodeType::Selector:
		type_str = "Selector";
		break;
	case BtNode::NodeType::Parallel:
		type_str = "Parallel";
		break;
	case BtNode::NodeType::Condition:
		type_str = "Condition";
		break;
	case BtNode::NodeType::Action:
		type_str = "Action";
		break;
	default:
		break;
	}
	return type_str;
}

std::string BtNodeManager::GetChild(BtNode* parent, BtNode* node)
{
	auto parent_name = parent->getClassName();
	auto child_name = node->getClassName();
	if (child_name == "")
		return parent_name + "has child(level " + std::to_string(node->getLevel()) +") class name is nullptr!";
	auto type = GetEnumToString(node->getNodeType());
	if (type == "")
		return child_name+" type is nullptr!";
	char buff[300];
	sprintf(buff, "auto %s = dynamic_cast <Bt%sNode*>(BT_Factory::Create(EBTNode::%s, \"%s\", %s));\n", child_name.c_str(), type.c_str(), type.c_str(), child_name.c_str(), parent_name.c_str());
	m_FileBuff += buff;
	for (int i = 0; i<node->m_ChildNode.size(); i++)
	{
		std::string ret = "successs!!!";
		ret = GetChild(node, node->m_ChildNode[i]);
		if (ret != "successs!!!")
			break;
	}
	return "successs!!!";
}

void BtNodeManager::onDraw()
{
	for (auto bt:m_NodeList)
	{
		bt->onDraw();
	}
}