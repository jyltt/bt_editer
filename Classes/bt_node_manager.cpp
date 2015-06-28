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
	auto class_name = m_RootNode->getClassName();
	if (class_name == "")
		return "m_RootNode class name is nullptr!";
	auto name = class_name + std::to_string(m_RootNode->getUUID());
	auto type = GetEnumToString(m_RootNode->getNodeType());
	if (type == "")
		return "m_RootNode type is nullptr!";
	char buff[300];
	sprintf(buff, "auto %s = new Bt%sNode(\"%s\");\nm_root = %s;\n", name.c_str(), type.c_str(), name.c_str(), name.c_str());
	m_FileBuff = buff;
	for (int i = 0; i < m_RootNode->GetChild().size(); i++)
	{
		std::string ret = "successs!!!";
		ret = GetChild(m_RootNode, m_RootNode->GetChild()[i]);
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
	auto parent_name = parent->getClassName()+std::to_string(parent->getUUID());
	auto class_name = node->getClassName();
	if (class_name == "")
		return parent_name + "has child(level " + std::to_string(node->getLevel()) +") class name is nullptr!";
	auto child_name = class_name+std::to_string(node->getUUID());
	auto type = GetEnumToString(node->getNodeType());
	if (type == "")
		return child_name+" type is nullptr!";
	char buff[300];
	switch (node->getNodeType())
	{
	case BtNode::NodeType::Action:
	case BtNode::NodeType::Condition:
		sprintf(buff, "auto %s = new %s(\"%s\");\n%s->AddChild(%s);\n", child_name.c_str(), class_name.c_str(), child_name.c_str(), parent_name.c_str(),child_name.c_str());
		break;
	default:
		sprintf(buff, "auto %s = new Bt%sNode(\"%s\");\n%s->AddChild(%s);\n", child_name.c_str(), type.c_str(), child_name.c_str(), parent_name.c_str(), child_name.c_str());
		break;
	}
	m_FileBuff += buff;
	for (int i = 0; i<node->GetChild().size(); i++)
	{
		std::string ret = "successs!!!";
		ret = GetChild(node, node->GetChild()[i]);
		if (ret != "successs!!!")
			break;
	}
	return "successs!!!";
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