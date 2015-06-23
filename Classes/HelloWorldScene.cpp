#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "bt_Node.h"
#include "bt_node_manager.h"

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
	isClick = false;
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

    return true;
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
	if (isClick)
	{
		isClick = false;
		onDoubleClick(ref);
	}
	else
	{
		isClick = true;
		scheduleOnce(CC_CALLBACK_1(HelloWorld::funcallback,this),0.4f,"click");
	}
}

void HelloWorld::funcallback(float time)
{
	isClick = false;
}

void HelloWorld::getAllChild(cocos2d::Node* parent,bool write_file)
{
}

void HelloWorld::WriteFile(cocos2d::Node* parent, cocos2d::Node* child)
{
	auto type = child->getName();
	char buff[300];
	auto child_name = ((ui::Button*)child)->getTitleText();
	auto parent_name = ((ui::Button*)parent)->getTitleText();
	sprintf(buff, "auto %s = dynamic_cast <Bt%sNode*>(BT_Factory::Create(EBTNode::%s, \"%s\", %s));\n",child_name.c_str(),type.c_str(),type.c_str(),child_name.c_str(),parent_name.c_str());
	file += buff;
	if (type == "Sequence")
	{
	}
	else if (type == "Selector")
	{
	}
	else if (type == "Parallel")
	{
	}
	else if (type == "Condition")
	{

	}
	else if (type == "Action")
	{

	}

}

void HelloWorld::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	BtNodeManager::getSingleton().onDraw();
}