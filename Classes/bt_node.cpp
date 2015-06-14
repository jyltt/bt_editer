#include "bt_Node.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio::timeline;
USING_NS_CC::ui;

BtNode::BtNode()
{
    auto rootNode = CSLoader::createNode("bt_node.csb");
    addChild(rootNode);

	m_LyotBk = (ui::Layout*)rootNode->getChildByName("bk");
	m_LyotBk->addTouchEventListener(CC_CALLBACK_2(onTouchMove, this));

	m_BtnNodeType = (ui::Button*)m_LyotBk->getChildByName("node_type");
	m_BtnNodeType->addClickEventListener(CC_CALLBACK_1(onChangeNodeType,this));

	m_BtnClassType = (ui::Button *)m_LyotBk->getChildByName("class_type");
	m_BtnClassType->addClickEventListener(CC_CALLBACK_1(onChangeClassType, this));

	m_BtnTop = (ui::Button *)m_LyotBk->getChildByName("top");
	m_BtnTop->addClickEventListener(CC_CALLBACK_1(onTopLevel, this));

	m_BtnDown = (ui::Button *)m_LyotBk->getChildByName("down");
	m_BtnDown->addClickEventListener(CC_CALLBACK_1(onDownLevel, this));

	m_BtnAdd = (ui::Button *)m_LyotBk->getChildByName("add");
	m_BtnAdd->addTouchEventListener(CC_CALLBACK_2(onAddNode, this));

	m_BtnDelete = (ui::Button *)m_LyotBk->getChildByName("delete");
	m_BtnDelete->addClickEventListener(CC_CALLBACK_1(onDelete, this));

	m_TextIndex = (ui::Text*)m_LyotBk->getChildByName("level");
	m_TextName = (ui::TextField*)m_LyotBk->getChildByName("class_name");
}

void BtNode::onChangeNodeType(Ref* obj)
{
	std::string name;
	switch (m_ENodeType)
	{
	case BtNode::NodeType::Sequence:
		m_ENodeType = NodeType::Selector;
		name = "Selector";
		break;
	case BtNode::NodeType::Selector:
		m_ENodeType = NodeType::Parallel;
		name = "Parallel";
		break;
	case BtNode::NodeType::Parallel:
		m_ENodeType = NodeType::Condition;
		name = "Condition";
		break;
	case BtNode::NodeType::Condition:
		m_ENodeType = NodeType::Action;
		name = "Action";
		break;
	case BtNode::NodeType::Action:
		m_ENodeType = NodeType::Sequence;
		name = "Sequence";
		break;
	default:
		break;
	}
	m_BtnNodeType->setName(name);
}

void BtNode::onChangeClassType(Ref* obj)
{
	std::string name;
	switch (m_EClassType)
	{
	case BtNode::ClassType::Function:
		m_EClassType = ClassType::Class;
		name = "Class";
		break;
	case BtNode::ClassType::Class:
		m_EClassType = ClassType::Function;
		name = "Function";
		break;
	default:
		break;
	}
	m_BtnClassType->setName(name);
}

void BtNode::onTopLevel(Ref* obj)
{

}

void BtNode::onDownLevel(Ref* obj)
{

}

void BtNode::onAddNode(Ref* obj, ui::Widget::TouchEventType type)
{
	Vec2 pt;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		pt = ((ui::Button*)obj)->getTouchMovePosition();
		pt = m_BtnAdd->getParent()->convertToNodeSpace(pt);
		if (m_AddLine == nullptr)
		{
			m_AddLine = new Line();
		}
		m_AddLine->a = m_LyotBk->getPosition();
		m_AddLine->b = pt;
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		pt = ((ui::Button*)obj)->getTouchEndPosition();
		pt = m_BtnAdd->getParent()->convertToNodeSpace(pt);
		if (m_AddLine)
		{
			delete m_AddLine;
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void BtNode::onDelete(Ref* obj)
{
	removeFromParent();
}

void BtNode::onTouchMove(Ref* obj, ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void BtNode::Update()
{
}

void BtNode::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	if (m_AddLine)
	{
		DrawPrimitives::drawLine(m_AddLine->a, m_AddLine->b);
	}
}

BtNode::~BtNode()
{
	delete m_AddLine;
}