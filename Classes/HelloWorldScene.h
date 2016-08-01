#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <list>
#include "bt_Node.h"
#include "tinyxml2/tinyxml2.h"
#include "menu_list.h"

class SaveDlg;
class TipLayer;
class OpenDlg;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init()override;
	void draw(Renderer *renderer, const Mat4& transform, uint32_t flags)override;

	BtNode *SetNode(cocos2d::Vec2 vec,ClassData *node_info);
	BtNode *SetNode(NodeInfo *node_info);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	void onDoubleClick(cocos2d::Ref* ref);
	void onClick(cocos2d::Ref* ref);
	void onChoseNode(cocos2d::Ref* obj);
	void onChangeAbortType(cocos2d::Ref* obj);
	void onCreateCode(cocos2d::Ref* ref);
	void onCloseInfo(cocos2d::Ref* ref);
	void onOpenInfo(cocos2d::Ref* ref);
	void onOpenFile(cocos2d::Ref* ref);
	void updateInfo();
	void funcallback(float time);
    BtNode *_CreateNode();
	BtNode* CreateNodeByInfo(NodeInfo *node);
	TipLayer *GetTipsDlg();
	OpenDlg *GetOpenDlg();
	SaveDlg *GetSaveDlg();

	ui::ScrollView* m_scroll;
	ui::ScrollView *m_scrInfo;
	ui::ListView *m_AttrList;
	ui::Text *m_fileClassName;
	ui::Text *m_labNodeType;
	ui::TextField *m_labNote;
	ui::Button *m_btnAbortType;
	ui::Button *m_btnClose;
	ui::Button *m_btnOpen;
	ui::Button *m_btnOpenFile;

	tinyxml2::XMLDocument *m_pDoc;
	bool m_isClick;
	MenuList *m_RightList=nullptr;
	SaveDlg *m_dlgSave=nullptr;
	TipLayer *m_TipsDlg = nullptr;
	OpenDlg *m_OpenDlg = nullptr;
};

#endif // __HELLOWORLD_SCENE_H__
