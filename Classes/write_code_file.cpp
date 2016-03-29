#include "write_code_file.h"
#include "xml_file.h"

WriteCodeFile::WriteCodeFile()
{ }

WriteCodeFile::~WriteCodeFile()
{ }

std::string WriteCodeFile::WriteFile(std::string xml_file, std::string file_name)
{
	auto _nodeInfo = XmlFile::getSingleton().ReadFileToNodeInfo(xml_file);
	if (_nodeInfo == nullptr)
		return "no find file:"+xml_file;
	auto class_name = _nodeInfo->cd->className;
	if (class_name == "")
		return "rootNode class name is nullptr!";
	auto name = class_name + std::to_string(_nodeInfo->uuid);
	auto type = Tools::GetEnumToString(_nodeInfo->cd->type);
	if (type == "")
		return "rootNode type is nullptr!";

	m_FileBuff = FileCreateNode(_nodeInfo->cd->type, name, class_name);
	m_FileBuff += FileSetAbort(_nodeInfo->abort_type, name);
	char buff[300];
	sprintf(buff, "m_root = %s; \n", name.c_str());
	m_FileBuff += buff;
	for (int i = 0; i < _nodeInfo->child_list.size(); i++)
	{
		std::string ret = "successs!!!";
		ret = GetChild(_nodeInfo, _nodeInfo->child_list[i]);
		if (ret != "successs!!!")
			return ret;
	}

	FILE *fp = fopen(file_name.c_str(), "wb");
	if (fp)
	{
		fwrite(m_FileBuff.c_str(), 1, strlen(m_FileBuff.c_str()), fp);
		fclose(fp);
		return "Write succeed";
	}
	else
		return "Write failed";
}

std::string WriteCodeFile::GetChild(NodeInfo* parent, NodeInfo* node)
{
	auto parent_name = parent->cd->className+std::to_string(parent->uuid);
	auto class_name = node->cd->className;
	auto child_name = class_name+std::to_string(node->uuid);
	auto e_type = node->cd->type;
	auto type = Tools::GetEnumToString(e_type);

	m_FileBuff += FileCreateNode(e_type, child_name, class_name);
	switch (e_type)
	{
	case NodeType::Action:
	case NodeType::Condition:
	case NodeType::Decorate:
		m_FileBuff += FileSetAttr(node->cd, child_name);
		break;
	default:
		m_FileBuff += FileSetAbort(node->abort_type, child_name);
		break;
	}
	m_FileBuff += FileAddChild(child_name, parent_name);

	std::string ret = "successs!!!";
	for (int i = 0; i<node->child_list.size(); i++)
	{
		ret = GetChild(node, node->child_list[i]);
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
