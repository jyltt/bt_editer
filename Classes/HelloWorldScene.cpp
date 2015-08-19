#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "bt_Node.h"
#include "bt_node_manager.h"
#include "read_file.h"
#include "attr_item.h"

USING_NS_CC;
using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
	m_isClick = false;
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");
    addChild(rootNode);
	m_scroll = (ui::ScrollView*)rootNode->getChildByName("bk");
	m_scroll->addClickEventListener(CC_CALLBACK_1(HelloWorld::onClick,this));
	auto inner = m_scroll->getInnerContainer();
	inner->setPosition(inner->getContentSize()/2*-1+m_scroll->getContentSize()/2);

	auto btn = (ui::Button*)rootNode->getChildByName("create");
	btn->addClickEventListener(CC_CALLBACK_1(HelloWorld::onCreateCode, this));

	m_bk = (ui::Layout *)rootNode->getChildByName("message");
	m_bk->addClickEventListener(CC_CALLBACK_1(HelloWorld::onClose, this));
	m_bk->setVisible(false);
	m_text = (ui::Text *)m_bk->getChildByName("text");

	m_btnOpen = (ui::Button *)rootNode->getChildByName("open");
	m_btnOpen->addClickEventListener(CC_CALLBACK_1(HelloWorld::onOpenInfo, this));
	m_btnOpen->setVisible(false);

	m_scrInfo = (ui::ScrollView*)rootNode->getChildByName("info");
	m_fileClassName = (ui::Text*)m_scrInfo->getChildByName("class_name");
	m_labNodeType = (ui::Text*)m_scrInfo->getChildByName("node_type");
	m_btnAbortType = (ui::Button *)m_scrInfo->getChildByName("abort_type");
	m_btnAbortType->addClickEventListener(CC_CALLBACK_1(HelloWorld::onChangeAbortType, this));
	m_btnClose = (ui::Button *)m_scrInfo->getChildByName("close");
	m_btnClose->addClickEventListener(CC_CALLBACK_1(HelloWorld::onCloseInfo, this));
	m_labNote = (ui::TextField*)m_scrInfo->getChildByName("note");
	m_AttrList = (ui::ListView*)m_scrInfo->getChildByName("attr_list");

	CreateNode();

    return true;
}

void HelloWorld::CreateNode()
{
	m_pDoc = new tinyxml2::XMLDocument();
	if (m_pDoc->LoadFile("bt.xml")== tinyxml2::XML_SUCCESS)
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

			// _node = BtNodeManager::getSingleton().CreateNode();
			// _node->setClickCallback(CC_CALLBACK_1(HelloWorld::onChoseNode, this));
			// _node->setNodeType((NodeType)node_type);
			// _node->setAbortType((AbortType)abort_type);
			// _node->setClassName(class_name);
			// _node->setUUID(uuid);
			// _node->setPosition(pos);
			// m_scroll->addChild(_node);
			ClassData cd;
			cd.className = class_name;
			cd.type = (NodeType)node_type;
			for (int i = 0; i<attr_list.size(); i++)
			{
				cd.attrList.push_back(attr_list[i]);
			}
			_node = SetNode(pos, &cd);
			_node->setAbortType((AbortType)abort_type);
			_node->setUUID(uuid);
			for (int i = 0; i<child_list.size(); i++)
			{
				auto id = child_list[i];
				_node->addNode(BtNodeManager::getSingleton().FindBtNode(id));
			}
		}
		BtNodeManager::getSingleton().setRootNode(_node);
	}
}

void HelloWorld::WriteFile()
{
	m_pDoc = new tinyxml2::XMLDocument();
	auto pDel = m_pDoc->NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
	m_pDoc->LinkEndChild(pDel);

	GetChild(BtNodeManager::getSingleton().getRootNode());

	m_pDoc->SaveFile("bt.xml");
	delete m_pDoc;
}

void HelloWorld::GetChild(BtNode* node)
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

void HelloWorld::onCreateCode(cocos2d::Ref* ref)
{
	m_bk->setVisible(true);
	m_text->setString(BtNodeManager::getSingleton().WriteFile());
	WriteFile();
}

void HelloWorld::onChangeAbortType(cocos2d::Ref* obj)
{
	auto node = BtNodeManager::getSingleton().getChoseNode();
	if (node)
	{
		node->onChangeAbortType(nullptr);
		updateInfo();
	}
}

void HelloWorld::onDoubleClick(cocos2d::Ref* ref)
{
	auto localPos = ((ui::Widget*)ref)->getTouchBeganPosition();
	auto inner = m_scroll->getInnerContainer();
	auto pos = inner->convertToNodeSpace(localPos);
	if (m_RightList == nullptr)
	{
		m_RightList = MenuList::create();
		m_RightList->SetFileList(ReadFile::getSingleton().GetDoc("root"));
		m_RightList->SetNodeRoot(this);
		m_scroll->addChild(m_RightList);
	}
	m_RightList->SetRootPosition(pos);
	m_RightList->setPosition(pos);
	m_RightList->setShow(true);
}

BtNode *HelloWorld::SetNode(cocos2d::Vec2 vec,ClassData *node_info)
{
	auto node = BtNodeManager::getSingleton().CreateNode();
	node->setClickCallback(CC_CALLBACK_1(HelloWorld::onChoseNode, this));
	node->setPosition(vec);
	node->setClassName(node_info->className);
	node->setNodeType(node_info->type);
	node->setUserData(new ClassData(node_info));
	m_scroll->addChild(node);

	if (m_RightList)
	{
		m_RightList->setShow(false);
		m_RightList->removeFromParent();
		m_RightList = nullptr;
	}
	return node;
}

void HelloWorld::onChoseNode(cocos2d::Ref* obj)
{
	BtNodeManager::getSingleton().setChoseNode((BtNode*)obj);
	updateInfo();
}

void HelloWorld::updateInfo()
{
	auto node = BtNodeManager::getSingleton().getChoseNode();
	if (node)
	{
		auto info = (ClassData*)node->getUserData();
		m_fileClassName->setString(node->getClassName());
		switch (node->getNodeType())
		{
		case NodeType::Sequence:
		case NodeType::Selector:
		case NodeType::Parallel:
			m_btnAbortType->setVisible(true);
			break;
		case NodeType::Condition:
		case NodeType::Action:
		case NodeType::Decorate:
			m_btnAbortType->setVisible(false);
			break;
		default:
			break;
		}
		m_btnAbortType->setTitleText(Tools::GetEnumToString(node->getAbortType()));
		m_labNodeType->setString(Tools::GetEnumToString(node->getNodeType()));
		auto &attrList = info->attrList;
		m_AttrList->removeAllItems(); 
		for (int i = 0; i<attrList.size(); i++)
		{
			auto item = AttrItem::create();
			item->SetAttr(attrList[0]);
			m_AttrList->addChild(item);
		}
		m_AttrList->refreshView();
	}
	else
	{
		m_fileClassName->setString("class name");
		m_labNodeType->setString("");
		m_AttrList->removeAllItems();
	}
}

void HelloWorld::onClick(cocos2d::Ref* ref)
{
	if (m_RightList)
	{
		m_RightList->setShow(false);
		m_RightList->removeFromParent();
		m_RightList = nullptr;
	}
	if (m_isClick)
	{
		m_isClick = false;
		onDoubleClick(ref);
	}
	else
	{
		m_isClick = true;
		scheduleOnce(CC_CALLBACK_1(HelloWorld::funcallback,this),0.4f,"click");
	}
}

void HelloWorld::funcallback(float time)
{
	m_isClick = false;
}

void HelloWorld::onClose(cocos2d::Ref* ref)
{
	m_bk->setVisible(false);
}

void HelloWorld::onCloseInfo(cocos2d::Ref* ref)
{
	m_scrInfo->setVisible(false);
	m_btnOpen->setVisible(true);
}

void HelloWorld::onOpenInfo(cocos2d::Ref* ref)
{
	m_scrInfo->setVisible(true);
	m_btnOpen->setVisible(false);
}

void HelloWorld::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	BtNodeManager::getSingleton().onDraw();
}