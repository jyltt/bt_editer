#include "write_code_file.h"

WriteCodeFile::WriteCodeFile()
{ }

WriteCodeFile::~WriteCodeFile()
{ }

std::string WriteCodeFile::WriteFile(BtNode *rootNode)
{
	if (rootNode == nullptr)
		return "rootNode is nullptr!";
	auto class_name = rootNode->getClassName();
	if (class_name == "")
		return "rootNode class name is nullptr!";
	auto name = class_name + std::to_string(rootNode->getUUID());
	auto type = Tools::GetEnumToString(rootNode->getNodeType());
	if (type == "")
		return "rootNode type is nullptr!";

	m_FileBuff = FileCreateNode(rootNode->getNodeType(), name, class_name);
	m_FileBuff += FileSetAbort(rootNode->getAbortType(), name);
	char buff[300];
	sprintf(buff, "m_root = %s; \n", name.c_str());
	m_FileBuff += buff;
	for (int i = 0; i < rootNode->GetChild().size(); i++)
	{
		std::string ret = "successs!!!";
		ret = GetChild(rootNode, rootNode->GetChild()[i]);
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

std::string WriteCodeFile::GetChild(BtNode* parent, BtNode* node)
{
	auto parent_name = parent->getClassName()+std::to_string(parent->getUUID());
	auto class_name = node->getClassName();
	if (class_name == "")
		return parent_name + " has child(level " + std::to_string(node->getLevel()) +") class name is nullptr!";
	auto child_name = class_name+std::to_string(node->getUUID());
	auto type = Tools::GetEnumToString(node->getNodeType());
	if (type == "")
		return child_name+" type is nullptr!";

	m_FileBuff += FileCreateNode(node->getNodeType(), child_name, class_name);
	switch (node->getNodeType())
	{
	case NodeType::Action:
	case NodeType::Condition:
	case NodeType::Decorate:
		m_FileBuff += FileSetAttr((ClassData*)node->getUserData(), child_name);
		break;
	default:
		m_FileBuff += FileSetAbort(node->getAbortType(), child_name);
		break;
	}
	m_FileBuff += FileAddChild(child_name, parent_name);

	std::string ret = "successs!!!";
	for (int i = 0; i<node->GetChild().size(); i++)
	{
		ret = GetChild(node, node->GetChild()[i]);
		if (ret != "successs!!!")
			break;
	}
	return ret;
}
std::string WriteCodeFile::FileCreateNode(NodeType type, std::string var, std::string class_name)
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
std::string WriteCodeFile::FileAddChild(std::string child, std::string parent)
{
	char buff[300];
	sprintf(buff, "%s->AddChild(%s);\n", parent.c_str(), child.c_str());
	return buff;
}
std::string WriteCodeFile::FileSetAbort(AbortType type, std::string var)
{
	char buff[300];
	sprintf(buff, "%s->setAbortType(EBTAbortType::%s);\n", var.c_str(), Tools::GetEnumToString(type).c_str());
	return buff;
}
std::string WriteCodeFile::FileSetAttr(ClassData *data, std::string var)
{
	std::string attr_str = "";
	char buff[600];
	auto &attr_list = data->attrList;
	for (auto attr:attr_list)
	{
		switch (attr->type)
		{
		case AttrType::number:
			sprintf(buff, "%s->set%s(%s);\n", var.c_str(), attr->name.c_str(), attr->str.c_str());
			break;
		case AttrType::string:
			sprintf(buff, "%s->set%s(\"%s\");\n", var.c_str(), attr->name.c_str(), attr->str.c_str());
		default:
			break;
		}
		attr_str += buff;
	}
	return attr_str;
}
