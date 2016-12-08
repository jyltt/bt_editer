#include "bt_Node.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "bt_node_manager.h"
#include "struct.h"
#include "Tools.h"

USING_NS_CC;
using namespace cocostudio::timeline;
USING_NS_CC::ui;

BtNode::BtNode()
	:m_AddLine(nullptr)
	, m_EAbortType(AbortType::none)
	, m_Index(-1)
	, m_ParentNode(nullptr)
{
    auto rootNode = CSLoader::createNode("bt_node.csb");
    addChild(rootNode);

	m_LyotBk = (ui::Layout*)rootNode->getChildByName("bk");
	m_LyotBk->addTouchEventListener(CC_CALLBACK_2(BtNode::onTouchMove, this));
	m_LyotBk->addClickEventListener(CC_CALLBACK_1(BtNode::onClick, this));

	m_labNodeType = (ui::Text*)m_LyotBk->getChildByName("node_type");

	m_BtnTop = (ui::Button *)m_LyotBk->getChildByName("top");
	m_BtnTop->addClickEventListener(CC_CALLBACK_1(BtNode::onTopLevel, this));

	m_BtnDown = (ui::Button *)m_LyotBk->getChildByName("down");
	m_BtnDown->addClickEventListener(CC_CALLBACK_1(BtNode::onDownLevel, this));

	m_BtnAdd = (ui::Button *)m_LyotBk->getChildByName("add");
	m_BtnAdd->addTouchEventListener(CC_CALLBACK_2(BtNode::onAddNode, this));

	m_BtnDelete = (ui::Button *)m_LyotBk->getChildByName("delete");
	m_BtnDelete->addClickEventListener(CC_CALLBACK_1(BtNode::onDelete, this));

	m_TextIndex = (ui::Text*)m_LyotBk->getChildByName("level");
	m_TextName = (ui::Text*)m_LyotBk->getChildByName("class_name");
	
	m_labAbortType = (ui::Text*)m_LyotBk->getChildByName("abort_type");
}

void BtNode::setInfo(NodeInfo *info)
{
    auto &data = info->cd;
    setClassData(&data);
    setClassName(data.className);
    setNodeType(data.type);
	setAbortType(info->abort_type);
	setUUID(info->uuid);
    setPosition(info->pos);
	if (info->isFailure)
	{
		m_LyotBk->setBackGroundColor(Color3B(255, 0, 0));
	}
	else
	{
		m_LyotBk->setBackGroundColor(Color3B(150, 200, 255));
	}
}

void BtNode::onChangeNodeType(Ref* obj)
{
	m_BtInfo->type = Tools::GetNextEnum(m_BtInfo->type);
	std::string name = Tools::GetEnumToString(m_BtInfo->type);
	m_labNodeType->setString(name);
	NodeTypeCfg(m_BtInfo->type);
}

void BtNode::onChangeAbortType(Ref* obj)
{
	m_EAbortType = Tools::GetNextEnum(m_EAbortType);
	std::string name = Tools::GetEnumToString(m_EAbortType);
	m_labAbortType->setString(name);
}

void BtNode::onTopLevel(Ref* obj)
{
	if (m_Index <= 1) return;
	if (m_ParentNode == nullptr) return;
	m_ParentNode->TopLevel(this);
}

void BtNode::onDownLevel(Ref* obj)
{
	if (m_Index == -1) return;
	if (m_ParentNode == nullptr) return;
	m_ParentNode->DownLevel(this);
}
bool BtNode::DownLevel(BtNode* node)
{
	if (node->getLevel() == m_ChildNode.size())
		return false;
	auto index = node->getLevel() - 1;
	m_ChildNode[index] = m_ChildNode[index+1];
	m_ChildNode[index]->setLevel(index+1);
	m_ChildNode[index+1] = node;
	node->setLevel(index+2);
	return true;
}
bool BtNode::TopLevel(BtNode* node)
{
	if (node->getLevel() <= 1) return false;
	auto index = node->getLevel() - 1;
	m_ChildNode[index] = m_ChildNode[index-1];
	m_ChildNode[index]->setLevel(index+1);
	m_ChildNode[index-1] = node;
	node->setLevel(index);
	return true;
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
	BtNodeManager::getSingleton().DeleteNode(this);
}

void BtNode::Delete()
{
	if (getParentNode())
	{
		getParentNode()->removeNode(this);
	}
	for (auto node:m_ChildNode)
	{
		node->setParentNode(nullptr);
	}
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

void BtNode::onClick(Ref* obj)
{
	m_callback(this);
}

void BtNode::setClickCallback(std::function<void(Ref*)> callback)
{
	m_callback = callback;
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
	auto local_pos = convertToNodeSpace(vec);
	auto box = m_LyotBk->getBoundingBox();
	return box.containsPoint(local_pos);
}
void BtNode::addNode(BtNode* node)
{
	if (hasNode(node)) return;
	if (node->hasNode(this,true)) return;

	if (node->getParentNode() != nullptr)
	{
		node->getParentNode()->removeNode(node);
	}
	if (m_BtInfo->type != NodeType::Decorate)
	{
		m_ChildNode.push_back(node);
		node->setParentNode(this);
		node->setLevel(m_ChildNode.size());
	}
	else
	{
		removeAllNode();
		m_ChildNode.push_back(node);
		node->setParentNode(this);
		node->setLevel(m_ChildNode.size());
	}
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
void BtNode::removeAllNode()
{
	for (int i = 0; i<m_ChildNode.size(); i++)
	{
		m_ChildNode[i]->setParentNode(nullptr);
		m_ChildNode[i]->setLevel(-1);
	}
	m_ChildNode.clear();
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
void BtNode::setUUID(int var)
{
    m_uuid = var;
}
int BtNode::getUUID()
{
    return m_uuid;
}

void BtNode::setAbortType(AbortType var)
{
	m_EAbortType = var;
	std::string name = Tools::GetEnumToString(m_EAbortType);
	m_labAbortType->setString(name);
}

AbortType BtNode::getAbortType()
{
	return m_EAbortType;
}

NodeType BtNode::getNodeType()
{
	return m_BtInfo->type;
}

void BtNode::setNodeType(NodeType node_type)
{
	m_BtInfo->type = node_type;
	std::string name = Tools::GetEnumToString(m_BtInfo->type);
	m_labNodeType->setString(name);
	NodeTypeCfg(m_BtInfo->type);
}
void BtNode::NodeTypeCfg(NodeType type)
{
	switch (m_BtInfo->type)
	{
	case NodeType::Sequence:
	case NodeType::Selector:
	case NodeType::Parallel:
		m_BtnAdd->setVisible(true);
		m_labAbortType->setVisible(true);
		break;
	case NodeType::Condition:
	case NodeType::Action:
		m_BtnAdd->setVisible(false);
		m_labAbortType->setVisible(false);
		break;
	case NodeType::Decorate:
		m_BtnAdd->setVisible(true);
		m_labAbortType->setVisible(false);
		break;
	default:
		break;
	}
}
std::string BtNode::getClassName()
{
	m_Name = m_TextName->getString();
	return m_Name;
}
void BtNode::setClassName(std::string var)
{
	m_Name = var;
	m_TextName->setString(var);
}

std::vector<BtNode*> BtNode::GetChild()
{
	return m_ChildNode;
}

BtNode::~BtNode()
{
	ClearData();
}