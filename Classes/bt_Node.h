#ifndef BT_NODE_H_
#define BT_NODE_H_

#include "cocos2d.h"
#include <vector>
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio::timeline;

class BtNode
	:public Node
{
public:
	enum class NodeType
	{
		Sequence,
		Selector,
		Parallel,
		Condition,
		Action,
	};
	enum class ClassType
	{
		Function,
		Class,
	};
	CREATE_FUNC(BtNode);
	BtNode();
	~BtNode();
	void Update();
	void onDraw();

	bool isTouch(Vec2 vec);
	void addNode(BtNode* node);
	void removeNode(BtNode* node);
	void ClearData();
	void Delete();
	bool TopLevel(BtNode* node);
	bool DownLevel(BtNode* node);
	CC_SYNTHESIZE(BtNode*, m_ParentNode, ParentNode);
	CC_SYNTHESIZE(int, m_uuid,UUID);
	CC_PROPERTY(int, m_Index, Level);
protected:
	struct Line
	{
		Line() {};
		Line(cocos2d::Vec2 a1, cocos2d::Vec2 b1)
		{
			a = a1;
			b = b1;
		}
		cocos2d::Vec2 b;
		cocos2d::Vec2 a;
	};
	void onChangeNodeType(Ref* obj);
	void onChangeClassType(Ref* obj);
	void onTopLevel(Ref* obj);
	void onDownLevel(Ref* obj);
	void onDelete(Ref* obj);
	void onTouchMove(Ref* obj,ui::Widget::TouchEventType type);
	void onAddNode(Ref* obj,ui::Widget::TouchEventType type);
	bool hasNode(BtNode* node,bool isDeep=false);

private:
	NodeType m_ENodeType;
	ClassType m_EClassType;
	std::string m_Name;
	Line *m_AddLine;
	std::vector<Line *> m_ChildLine;
	std::vector<BtNode*> m_ChildNode;

	ui::Layout *m_LyotBk;
	ui::Button *m_BtnNodeType;
	ui::Button *m_BtnClassType;
	ui::Button *m_BtnTop;
	ui::Button *m_BtnDown;
	ui::Button *m_BtnAdd;
	ui::Button *m_BtnDelete;
	ui::Text *m_TextIndex;
	ui::TextField *m_TextName;
};
#endif