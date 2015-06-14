#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "bt_Node.h"

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
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");
    addChild(rootNode);

    return true;
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
	for (auto bt:m_list)
	{
		bt->Update();
	}
	m_rect.clear();
	getAllChild(root,false);
	for (auto line :m_rect)
	{
		DrawPrimitives::drawLine(line.a, line.b);
	}
}