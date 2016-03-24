#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "bt_Node.h"
#include "bt_node_manager.h"
#include "read_file.h"
#include "attr_item.h"
#include "write_code_file.h"
#include "xml_file.h"

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

	//CreateNode();
	auto root = XmlFile::getSingleton().CreateNode("bt.xml", CC_CALLBACK_2(HelloWorld::SetNode, this));
	BtNodeManager::getSingleton().setRootNode(root);

    return true;
}

void HelloWorld::onCreateCode(cocos2d::Ref* ref)
{
	m_bk->setVisible(true);
	auto root = BtNodeManager::getSingleton().getRootNode();
	auto des = WriteCodeFile::getSingleton().WriteFile(root);
	m_text->setString(des);
	//WriteFile();
	XmlFile::getSingleton().WriteFile(BtNodeManager::getSingleton().getRootNode(),"bt.xml");
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