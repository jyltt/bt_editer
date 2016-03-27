#include "xml_file.h"

XmlFile::XmlFile()
{ }

XmlFile::~XmlFile()
{ }

void XmlFile::WriteFile(BtNode* root,std::string name)
{
	m_pDoc = new tinyxml2::XMLDocument();
	auto pDel = m_pDoc->NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
	m_pDoc->LinkEndChild(pDel);

	auto node = GetChild(root);
	m_pDoc->LinkEndChild(node);

	m_pDoc->SaveFile(name.c_str());
	delete m_pDoc;
}

tinyxml2::XMLNode* XmlFile::GetChild(BtNode* node)
{
	auto class_type = node->getNodeType();
	auto abort_type = node->getAbortType();
	auto text = node->getClassName();
	int uuid = node->getUUID();
	auto pos = node->getPosition();
	auto class_data = (ClassData*)node->getUserData();

	auto n_node = m_pDoc->NewElement("node");
	{
		n_node->SetAttribute("class_name", text.c_str());
		n_node->SetAttribute("type", (int)class_type);
		n_node->SetAttribute("abort", (int)abort_type);
		n_node->SetAttribute("uuid", uuid);
		n_node->SetAttribute("x", pos.x);
		n_node->SetAttribute("y", pos.y);

		//属性
		auto &attr_list = class_data->attrList;
		auto n_attrList = m_pDoc->NewElement("attr");
		for (auto attr:attr_list)
		{
			auto n_attr = m_pDoc->NewElement("attr");
			n_attr->SetAttribute("attr_name", attr->name.c_str());
			n_attr->SetAttribute("attr_value", attr->str.c_str());
			n_attr->SetAttribute("attr_type", (int)attr->type);
			n_attrList->LinkEndChild(n_attr);
		}
		n_node->LinkEndChild(n_attrList);

		// 子节点
		auto n_child = m_pDoc->NewElement("child");
		for (int i = 0; i< node->GetChild().size(); i++)
		{
			auto n = node->GetChild()[i];
			auto node = GetChild(n);
			n_child->LinkEndChild(node);
		}
		n_node->LinkEndChild(n_child);
	}
	return n_node;
}

BtNode* XmlFile::CreateNode(std::string name, std::function<BtNode *(cocos2d::Vec2, ClassData*)> set_node)
{
	m_pDoc = new tinyxml2::XMLDocument();
	if (m_pDoc->LoadFile(name.c_str())== tinyxml2::XML_SUCCESS)
	{
		auto root = m_pDoc->RootElement();
		return CreateChild(root,set_node);
	}
	return nullptr;
}

BtNode *XmlFile::CreateChild(tinyxml2::XMLElement* node, std::function<BtNode *(cocos2d::Vec2, ClassData*)> set_node)
{
	BtNode *_node;
	ClassData cd;
	cd.type = (NodeType)node->IntAttribute("type");
	cd.className = node->Attribute("class_name");
	int abort_type = node->IntAttribute("abort");
	int uuid = node->IntAttribute("uuid");
	Vec2 pos;
	pos.x = node->IntAttribute("x");
	pos.y = node->IntAttribute("y");

	auto child_node = node->FirstChildElement("attr");
	auto attr = child_node->FirstChildElement();
	while (attr)
	{
		auto a = new Attr();
		a->name = attr->Attribute("attr_name");
		a->str = attr->Attribute("attr_value");
		a->type = (AttrType)attr->IntAttribute("attr_type");
		cd.attrList.push_back(a);
		attr = attr->NextSiblingElement();
	}
	_node = set_node(pos, &cd);
	_node->setAbortType((AbortType)abort_type);
	_node->setUUID(uuid);

	child_node = child_node->NextSiblingElement("child");
	auto n_child = child_node->FirstChildElement();
	while (n_child)
	{
		auto child = CreateChild(n_child, set_node);
		_node->addNode(child);
		n_child = n_child->NextSiblingElement();
	}
	return _node;
}
