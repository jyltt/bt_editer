#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "bt_Node.h"
#include "bt_node_manager.h"
#include "file_manager.h"
#include "attr_item.h"
#include "write_code_file.h"
#include "xml_file.h"
#include "save_dlg.h"
#include "tip_layer.h"
#include "open_dlg.h"
#include "menu_list.h"
#include "struct.h"
#include "Tools.h"

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

	m_btnOpen = (ui::Button *)rootNode->getChildByName("open");
	m_btnOpen->addClickEventListener(CC_CALLBACK_1(HelloWorld::onOpenInfo, this));
	m_btnOpen->setVisible(false);

	m_btnOpenFile = (ui::Button *)rootNode->getChildByName("btn_open");
	m_btnOpenFile->addClickEventListener(CC_CALLBACK_1(HelloWorld::onOpenFile, this));

	m_btnClear = (ui::Button *)rootNode->getChildByName("btn_clear");
	m_btnClear->addClickEventListener(CC_CALLBACK_1(HelloWorld::onClear, this));

	m_scrInfo = (ui::ScrollView*)rootNode->getChildByName("info");
	m_fileClassName = (ui::Text*)m_scrInfo->getChildByName("class_name");
	m_labNodeType = (ui::Text*)m_scrInfo->getChildByName("node_type");
	m_btnAbortType = (ui::Button *)m_scrInfo->getChildByName("abort_type");
	m_btnAbortType->addClickEventListener(CC_CALLBACK_1(HelloWorld::onChangeAbortType, this));
	m_btnClose = (ui::Button *)m_scrInfo->getChildByName("close");
	m_btnClose->addClickEventListener(CC_CALLBACK_1(HelloWorld::onCloseInfo, this));
	m_labNote = (ui::TextField*)m_scrInfo->getChildByName("note");
	m_AttrList = (ui::ListView*)m_scrInfo->getChildByName("attr_list");

	//CreateNode();
	FileManager::getSingleton().Init();

    return true;
}

void HelloWorld::OpenFile(std::string name)
{
	auto node = XmlFile::getSingleton().ReadFileToNodeInfo(name);
    if (node)
    {
        auto root = CreateNodeByInfo(node);
        BtNodeManager::getSingleton().setRootNode(root);
    }
}

BtNode* HelloWorld::CreateNodeByInfo(NodeInfo *node)
{
	BtNode*_node;
	//auto *cd = &node->cd;
	//AbortType abort_type = node->abort_type;
	//int uuid = node->uuid;
	//Vec2 pos = node->pos;

	_node = SetNode(node);
	//_node->setAbortType(abort_type);
	//_node->setUserData(cd);
	//_node->setUUID(uuid);

	for (auto n_child : node->child_list)
	{
		auto child = CreateNodeByInfo(n_child);
		_node->addNode(child);
	}
	return _node;
}

void HelloWorld::onCreateCode(cocos2d::Ref* ref)
{
	//auto root = BtNodeManager::getSingleton().getRootNode();
	//XmlFile::getSingleton().WriteFile(root,"bt.xml");
	//auto des = WriteCodeFile::getSingleton().WriteFile("bt.xml", "bt_tree.txt");
	//m_text->setString(des);
	//WriteFile();
	GetSaveDlg()->setVisible(true);
}

void HelloWorld::onChangeAbortType(cocos2d::Ref* obj)
{
	auto node = BtNodeManager::getSingleton().getChoseNode();
	if (node)
	{
		node->onChangeAbortType(nullptr);
	}
	updateInfo();
}

void HelloWorld::onDoubleClick(cocos2d::Ref* ref)
{
	auto localPos = ((ui::Widget*)ref)->getTouchBeganPosition();
	auto inner = m_scroll->getInnerContainer();
	auto pos = inner->convertToNodeSpace(localPos);
	if (m_RightList == nullptr)
	{
		m_RightList = MenuList::create();
		m_RightList->SetFileList(FileManager::getSingleton().GetFileTree());
		m_RightList->SetNodeRoot(this);
		m_scroll->addChild(m_RightList);
	}
	m_RightList->SetRootPosition(pos);
	m_RightList->setPosition(pos);
	m_RightList->setShow(true);
}

BtNode *HelloWorld::SetNode(NodeInfo *node_info)
{
    auto node = _CreateNode();
    node->setInfo(node_info);

	return node;
}
BtNode *HelloWorld::SetNode(Vec2 vec, ClassData* node_info)
{
    auto node = _CreateNode();
	node->setPosition(vec);
	node->setClassData(node_info);
	node->setClassName(node_info->className);
	node->setNodeType(node_info->type);

	return node;
}
BtNode *HelloWorld::_CreateNode()
{
	auto node = BtNodeManager::getSingleton().CreateNode();
	node->setClickCallback(CC_CALLBACK_1(HelloWorld::onChoseNode, this));
    
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
		auto info = node->getClassData();
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
		for (auto attr:attrList)
		{
			auto item = AttrItem::create();
			item->SetAttr(attr.second);
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

void HelloWorld::onOpenFile(cocos2d::Ref* ref)
{
	//BtNodeManager::getSingleton().ClearNode();
	GetOpenDlg()->UpdateItem();
	GetOpenDlg()->setVisible(true);
}

void HelloWorld::onClear(cocos2d::Ref* ref)
{
	BtNodeManager::getSingleton().ClearNode();
}

void HelloWorld::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	BtNodeManager::getSingleton().onDraw();
}

TipLayer *HelloWorld::GetTipsDlg()
{
	if (m_TipsDlg == nullptr)
	{
		m_TipsDlg = TipLayer::create();
		addChild(m_TipsDlg,1000);
	}
	return m_TipsDlg;
}

OpenDlg *HelloWorld::GetOpenDlg()
{
	if (m_OpenDlg == nullptr)
	{
		m_OpenDlg = OpenDlg::create();
		m_OpenDlg->SetTipsDlg(GetTipsDlg());
		m_OpenDlg->SetOpenFileFunc(CC_CALLBACK_1(HelloWorld::OpenFile, this));
		addChild(m_OpenDlg);
	}
	return m_OpenDlg;
}

SaveDlg *HelloWorld::GetSaveDlg()
{
	if (m_dlgSave == nullptr)
	{
		m_dlgSave = SaveDlg::create();
		m_dlgSave->SetTipsDlg(GetTipsDlg());
		addChild(m_dlgSave);
	}
	return m_dlgSave;
}
