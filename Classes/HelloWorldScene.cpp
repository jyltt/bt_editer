#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "bt_Node.h"
#include "bt_node_manager.h"
#include "tinyxml2/tinyxml2.h"

USING_NS_CC;
using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	m_isClick = false;
    //////////////////////////////
    // 1. super init first
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

	HelloWorld::CreateNode();

    return true;
}

void HelloWorld::CreateNode()
{

}

void HelloWorld::WriteFile()
{
	auto pDoc = new tinyxml2::XMLDocument();
	auto pDel = pDoc->NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
	pDoc->LinkEndChild(pDel);

	pDoc->SaveFile("bt.txt");
}

void HelloWorld::onCreateCode(cocos2d::Ref* ref)
{
	m_bk->setVisible(true);
	m_text->setString(BtNodeManager::getSingleton().WriteFile());
	WriteFile();
}

void HelloWorld::onDoubleClick(cocos2d::Ref* ref)
{
	auto node = BtNodeManager::getSingleton().CreateNode();
	auto localPos = ((ui::Widget*)ref)->getTouchBeganPosition();
	auto inner = m_scroll->getInnerContainer();
	auto pos = inner->convertToNodeSpace(localPos);
	node->setPosition(pos);
	m_scroll->addChild(node);
}

void HelloWorld::onClick(cocos2d::Ref* ref)
{
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

void HelloWorld::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	BtNodeManager::getSingleton().onDraw();
}