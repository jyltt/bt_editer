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

	GetChild(root);

	m_pDoc->SaveFile(name.c_str());
	delete m_pDoc;
}

void XmlFile::GetChild(BtNode* node)
{
	auto class_type = node->getNodeType();
	auto abort_type = node->getAbortType();
	auto text = node->getClassName();
	int uuid = node->getUUID();
	auto pos = node->getPosition();
	auto class_data = (ClassData*)node->getUserData();
	std::vector<int> child_name;

	for (int i = 0; i< node->GetChild().size(); i++)
	{
		auto n = node->GetChild()[i];
		GetChild(n);
		child_name.push_back(n->getUUID());
	}

	auto n_node = m_pDoc->NewElement("node");
	{
		// 节点类型
		auto n_type = m_pDoc->NewElement("type");
		n_type->LinkEndChild(m_pDoc->NewText(std::to_string((int)class_type).c_str()));
		n_node->LinkEndChild(n_type);

		// 打断类型
		auto a_type = m_pDoc->NewElement("abort");
		a_type->LinkEndChild(m_pDoc->NewText(std::to_string((int)abort_type).c_str()));
		n_node->LinkEndChild(a_type);

		// 唯一id 
		auto n_uuid = m_pDoc->NewElement("uuid");
		n_uuid->LinkEndChild(m_pDoc->NewText(std::to_string((int)uuid).c_str()));
		n_node->LinkEndChild(n_uuid);

		// 位置
		auto n_pos = m_pDoc->NewElement("pos");
		{
			auto x = m_pDoc->NewElement("x");
			x->LinkEndChild(m_pDoc->NewText(std::to_string(pos.x).c_str()));
			n_pos->LinkEndChild(x);
			auto y = m_pDoc->NewElement("y");
			y->LinkEndChild(m_pDoc->NewText(std::to_string(pos.y).c_str()));
			n_pos->LinkEndChild(y);
		}
		n_node->LinkEndChild(n_pos);

		// 属性
		auto &attr_list = class_data->attrList;
		auto n_attr = m_pDoc->NewElement("attr");
		{
			for (auto attr:attr_list)
			{
				auto attr_e = m_pDoc->NewElement(attr->name.c_str());
				{
					auto value = m_pDoc->NewElement("value");
					value->LinkEndChild(m_pDoc->NewText(attr->str.c_str()));
					attr_e->LinkEndChild(value);
					auto type = m_pDoc->NewElement("type");
					type->LinkEndChild(m_pDoc->NewText(std::to_string((int)attr->type).c_str()));
					attr_e->LinkEndChild(type);
				}
				n_attr->LinkEndChild(attr_e);
			}
		}
		n_node->LinkEndChild(n_attr);

		// 类名
		auto n_text = m_pDoc->NewElement("class_name");
		n_text->LinkEndChild(m_pDoc->NewText(text.c_str()));
		n_node->LinkEndChild(n_text);

		// 子节点
		auto n_child = m_pDoc->NewElement("child");
		{
			for (int i = 0; i<child_name.size(); i++)
			{
				auto n_child_name = m_pDoc->NewElement("name_id");
				n_child_name->LinkEndChild(m_pDoc->NewText(std::to_string(child_name[i]).c_str()));
				n_child->LinkEndChild(n_child_name);
			}
		}
		n_node->LinkEndChild(n_child);

	}
	m_pDoc->LinkEndChild(n_node);
}

BtNode* XmlFile::CreateNode(std::string name, std::function<BtNode *(cocos2d::Vec2, ClassData*)> set_node)
{
	m_pDoc = new tinyxml2::XMLDocument();
	if (m_pDoc->LoadFile(name.c_str())== tinyxml2::XML_SUCCESS)
	{
		auto root = m_pDoc->RootElement();
		tinyxml2::XMLElement *node = root;
		BtNode *_node;
		while (node)
		{
			int node_type;
			int abort_type;
			int uuid;
			Vec2 pos;
			std::string class_name;
			std::vector<int> child_list;
			std::vector<Attr*> attr_list;

			auto n_type = node->FirstChildElement();
			node_type = atoi(n_type->GetText());
			auto a_type = n_type->NextSiblingElement();
			abort_type = atoi(a_type->GetText());
			auto n_uuid = a_type->NextSiblingElement();
			uuid = atoi(n_uuid->GetText());
			auto n_pos = n_uuid->NextSiblingElement();
			{
				auto n_x = n_pos->FirstChildElement();
				pos.x = atof(n_x->GetText());
				auto n_y = n_x->NextSiblingElement();
				pos.y = atof(n_y->GetText());
			}
			auto n_attr = n_pos->NextSiblingElement();
			{
				auto attr = n_attr->FirstChildElement();
				while (attr)
				{
					auto a = new Attr();
					a->name = attr->Name();
					{
						auto value = attr->FirstChildElement();
						a->str = value->GetText();
						auto type = value->NextSiblingElement();
						a->type = (AttrType)atoi(type->GetText());
					}
					attr_list.push_back(a);
					attr = attr->NextSiblingElement();
				}
			}
			auto n_className = n_attr->NextSiblingElement();
			class_name = n_className->GetText();
			auto n_childlist = n_className->NextSiblingElement();
			auto n_child = n_childlist->FirstChildElement();
			while (n_child)
			{
				child_list.push_back(atoi(n_child->GetText()));
				n_child = n_child->NextSiblingElement();
			}
			node = node->NextSiblingElement();

			ClassData cd;
			cd.className = class_name;
			cd.type = (NodeType)node_type;
			for (int i = 0; i<attr_list.size(); i++)
			{
				cd.attrList.push_back(attr_list[i]);
			}
			_node = set_node(pos, &cd);
			_node->setAbortType((AbortType)abort_type);
			_node->setUUID(uuid);
			for (int i = 0; i<child_list.size(); i++)
			{
				auto id = child_list[i];
				_node->addNode(BtNodeManager::getSingleton().FindBtNode(id));
			}
		}
		return _node;
	}
	return nullptr;
}
