#ifndef BT_NODE_H_
#define BT_NODE_H_

#include "cocos2d.h"
#include <vector>
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

struct ClassData;
struct NodeInfo;
enum class AbortType;
enum class NodeType;

USING_NS_CC;
using namespace cocostudio::timeline;

class BtNode
	:public Node
{
public:
	CREATE_FUNC(BtNode);
	BtNode();
	~BtNode();
	void Update();
	void onDraw();

	bool isTouch(Vec2 vec);
	void addNode(BtNode* node);
	void removeNode(BtNode* node);
	void removeAllNode();
	void ClearData();
	void Delete();
	bool TopLevel(BtNode* node);
	bool DownLevel(BtNode* node);
	void setClickCallback(std::function<void(Ref*)> callback);
	void onChangeNodeType(Ref* obj);
	void onChangeAbortType(Ref* obj);
	CC_SYNTHESIZE(BtNode*, m_ParentNode, ParentNode);
	CC_SYNTHESIZE(ClassData*, m_BtInfo, ClassData);
	CC_PROPERTY(int, m_uuid,UUID);
	CC_PROPERTY(int, m_Index, Level);
	CC_PROPERTY(NodeType, m_ENodeType,NodeType);
	CC_PROPERTY(AbortType, m_EAbortType,AbortType);
	CC_PROPERTY(std::string, m_Name, ClassName);
    void setInfo(NodeInfo* info);
	std::vector<BtNode*> GetChild();
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
	void onClick(Ref* obj);
	void onTopLevel(Ref* obj);
	void onDownLevel(Ref* obj);
	void onDelete(Ref* obj);
	void onTouchMove(Ref* obj,ui::Widget::TouchEventType type);
	void onAddNode(Ref* obj,ui::Widget::TouchEventType type);
	bool hasNode(BtNode* node,bool isDeep=false);
	void NodeTypeCfg(NodeType type);

private:
	Line *m_AddLine;
	std::vector<Line *> m_ChildLine;
	std::vector<BtNode*> m_ChildNode;
	std::function<void(Ref*)> m_callback;

	ui::Layout *m_LyotBk;
	ui::Button *m_BtnTop;
	ui::Button *m_BtnDown;
	ui::Button *m_BtnAdd;
	ui::Button *m_BtnDelete;
	ui::Text *m_labNodeType;
	ui::Text *m_labAbortType;
	ui::Text *m_TextIndex;
	ui::Text *m_TextName;
};
#endif