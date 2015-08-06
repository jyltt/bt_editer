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
			if (getChoseNode() && node->getUUID() == getChoseNode()->getUUID())
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

std::string BtNodeManager::WriteFile()
{
	if (m_RootNode == nullptr)
		return "m_RootNode is nullptr!";
	auto class_name = m_RootNode->getClassName();
	if (class_name == "")
		return "m_RootNode class name is nullptr!";
	auto name = class_name + std::to_string(m_RootNode->getUUID());
	auto type = Tools::GetEnumToString(m_RootNode->getNodeType());
	if (type == "")
		return "m_RootNode type is nullptr!";

	m_FileBuff = FileCreateNode(m_RootNode->getNodeType(),name,class_name);
	m_FileBuff += FileSetAbort(m_RootNode->getAbortType(), name);
	char buff[300];
	sprintf(buff, "m_root = %s; \n",name.c_str());
	m_FileBuff += buff;
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

std::string BtNodeManager::GetChild(BtNode* parent, BtNode* node)
{
	auto parent_name = parent->getClassName()+std::to_string(parent->getUUID());
	auto class_name = node->getClassName();
	if (class_name == "")
		return parent_name + " has child(level " + std::to_string(node->getLevel()) +") class name is nullptr!";
	auto child_name = class_name+std::to_string(node->getUUID());
	auto type = Tools::GetEnumToString(node->getNodeType());
	if (type == "")
		return child_name+" type is nullptr!";

	m_FileBuff += FileCreateNode(node->getNodeType(),child_name,class_name);
	switch (node->getNodeType())
	{
	case NodeType::Action:
	case NodeType::Condition:
	case NodeType::Decorate:
		break;
	default:
		m_FileBuff += FileSetAbort(node->getAbortType(), child_name);
		break;
	}
	m_FileBuff += FileAddChild(child_name,parent_name);

	std::string ret = "successs!!!";
	for (int i = 0; i<node->GetChild().size(); i++)
	{
		ret = GetChild(node, node->GetChild()[i]);
		if (ret != "successs!!!")
			break;
	}
	return ret;
}
std::string BtNodeManager::FileCreateNode(NodeType type, std::string var, std::string class_name)
{
	char buff[300];
	switch (type)
	{
	case NodeType::Action:
	case NodeType::Condition:
	case NodeType::Decorate:
		sprintf(buff, "auto %s = BT_Create(%s,\"%s\");\n", var.c_str(), class_name.c_str(), class_name.c_str());
		break;
	default:
		sprintf(buff, "auto %s = BT_Create(Bt%sNode,\"%s\");\n", var.c_str(), Tools::GetEnumToString(type).c_str(), class_name.c_str());
		break;
	}
	return buff;
}
std::string BtNodeManager::FileAddChild(std::string child, std::string parent)
{
	char buff[300];
	sprintf(buff, "%s->AddChild(%s);\n",parent.c_str(),child.c_str());
	return buff;
}
std::string BtNodeManager::FileSetAbort(AbortType type, std::string var)
{
	char buff[300];
	sprintf(buff, "%s->setAbortType(EBTAbortType::%s);\n",var.c_str(),Tools::GetEnumToString(type).c_str());
	return buff;
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