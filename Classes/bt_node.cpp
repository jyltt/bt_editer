#include "bt_Node.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "bt_node_manager.h"

USING_NS_CC;
using namespace cocostudio::timeline;
USING_NS_CC::ui;

BtNode::BtNode()
	:m_AddLine(nullptr)
	, m_ENodeType(NodeType::Sequence)
	, m_EClassType(ClassType::Class)
	, m_Index(-1)
	, m_ParentNode(nullptr)
{
    auto rootNode = CSLoader::createNode("bt_node.csb");
    addChild(rootNode);

	m_LyotBk = (ui::Layout*)rootNode->getChildByName("bk");
	m_LyotBk->addTouchEventListener(CC_CALLBACK_2(BtNode::onTouchMove, this));

	m_BtnNodeType = (ui::Button*)m_LyotBk->getChildByName("node_type");
	m_BtnNodeType->addClickEventListener(CC_CALLBACK_1(BtNode::onChangeNodeType,this));

	m_BtnClassType = (ui::Button *)m_LyotBk->getChildByName("class_type");
	m_BtnClassType->addClickEventListener(CC_CALLBACK_1(BtNode::onChangeClassType, this));

	m_BtnTop = (ui::Button *)m_LyotBk->getChildByName("top");
	m_BtnTop->addClickEventListener(CC_CALLBACK_1(BtNode::onTopLevel, this));

	m_BtnDown = (ui::Button *)m_LyotBk->getChildByName("down");
	m_BtnDown->addClickEventListener(CC_CALLBACK_1(BtNode::onDownLevel, this));

	m_BtnAdd = (ui::Button *)m_LyotBk->getChildByName("add");
	m_BtnAdd->addTouchEventListener(CC_CALLBACK_2(BtNode::onAddNode, this));

	m_BtnDelete = (ui::Button *)m_LyotBk->getChildByName("delete");
	m_BtnDelete->addClickEventListener(CC_CALLBACK_1(BtNode::onDelete, this));

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
		m_BtnAdd->setVisible(true);
		break;
	case BtNode::NodeType::Selector:
		m_ENodeType = NodeType::Parallel;
		name = "Parallel";
		m_BtnAdd->setVisible(true);
		break;
	case BtNode::NodeType::Parallel:
		m_ENodeType = NodeType::Condition;
		name = "Condition";
		m_BtnAdd->setVisible(false);
		break;
	case BtNode::NodeType::Condition:
		m_ENodeType = NodeType::Action;
		name = "Action";
		m_BtnAdd->setVisible(false);
		break;
	case BtNode::NodeType::Action:
		m_ENodeType = NodeType::Sequence;
		name = "Sequence";
		m_BtnAdd->setVisible(true);
		break;
	default:
		break;
	}
	m_BtnNodeType->setTitleText(name);
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
	m_BtnClassType->setTitleText(name);
}

void BtNode::onTopLevel(Ref* obj)
{
	if (m_Index == -1) return;

}

void BtNode::onDownLevel(Ref* obj)
{
	if (m_Index == -1) return;

}

void BtNode::onAddNode(Ref* obj, ui::Widget::TouchEventType type)
{
	ui::Button *o = (ui::Button *)obj;
	Vec2 pt;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		pt = o->getTouchMovePosition();
		if (m_AddLine == nullptr)
		{
			m_AddLine = new Line();
		}
		m_AddLine->a = m_BtnAdd->getParent()->convertToWorldSpace(m_BtnAdd->getPosition());
		m_AddLine->b = pt;
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		if (m_AddLine)
		{
			delete m_AddLine;
			m_AddLine = nullptr;
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
	{
		pt = o->getTouchEndPosition();
		if (m_AddLine)
		{
			delete m_AddLine;
			m_AddLine = nullptr;
		}
		auto node = BtNodeManager::getSingleton().TouchNode(pt);
		if (node != nullptr)
		{
			addNode(node);
		}
	}
	break;
	default:
		break;
	}
}

void BtNode::onDelete(Ref* obj)
{
}

void BtNode::Delete()
{
	removeFromParent();
}

void BtNode::onTouchMove(Ref* obj, ui::Widget::TouchEventType type)
{
	ui::Button *o = (ui::Button *)obj;
	Vec2 pt;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		pt = o->getTouchBeganPosition();
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		pt = o->getTouchMovePosition();
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		pt = o->getTouchEndPosition();
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
	pt = getParent()->convertToNodeSpace(pt);
	setPosition(pt);
}

void BtNode::Update()
{
}

void BtNode::onDraw()
{
	if (m_AddLine)
	{
		DrawPrimitives::drawLine(m_AddLine->a, m_AddLine->b);
	}
	auto point = getParent()->convertToWorldSpace(getPosition());
	for (auto node:m_ChildNode)
	{
		auto pos = node->getParent()->convertToWorldSpace(node->getPosition());
		DrawPrimitives::drawLine(point,pos);
	}
}

bool BtNode::isTouch(Vec2 vec)
{
	auto local_pos = m_LyotBk->convertToNodeSpace(vec);
	return m_LyotBk->getBoundingBox().containsPoint(local_pos);
}
void BtNode::addNode(BtNode* node)
{
	if (hasNode(node)) return;
	if (node->hasNode(this,true)) return;

	if (node->getParentNode() != nullptr)
	{
		node->getParentNode()->removeNode(node);
	}
	m_ChildNode.push_back(node);
	node->setParentNode(this);
	node->setLevel(m_ChildNode.size());
}
bool BtNode::hasNode(BtNode* node,bool isDeep)
{
	for (auto n:m_ChildNode)
	{
		if (node->getUUID() == n->getUUID())
		{
			return true;
		}
		if (isDeep && n->hasNode(node))
		{
			return true;
		}
	}
	return false;
}
void BtNode::removeNode(BtNode* node)
{
	node->setParentNode(nullptr);
	node->setLevel(-1);
	for (int i = 0; i<m_ChildNode.size(); i++)
	{
		if (m_ChildNode[i]->getUUID() == node->getUUID())
		{
			if (i+1 < m_ChildNode.size())
			{
				m_ChildNode[i] = m_ChildNode[i+1];
				m_ChildNode[i]->setLevel(i+1);
				node = m_ChildNode[i];
			}
		}
	}
	m_ChildNode.pop_back();
}
void BtNode::ClearData()
{
	delete m_AddLine;
	m_ChildNode.clear();
}
void BtNode::setLevel(int var)
{
	m_Index = var;
	m_TextIndex->setString(std::to_string(var));
}
int BtNode::getLevel()
{
	return m_Index;
}

BtNode::~BtNode()
{
	ClearData();
}