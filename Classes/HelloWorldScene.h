#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <list>
#include "bt_Node.h"
#include "tinyxml2/tinyxml2.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	void draw(Renderer *renderer, const Mat4& transform, uint32_t flags)override;

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	void onDoubleClick(cocos2d::Ref* ref);
	void onClick(cocos2d::Ref* ref);
	void onClose(cocos2d::Ref* ref);
	void onChoseNode(cocos2d::Ref* obj);
	void onChangeNodeType(cocos2d::Ref* obj);
	void onChangeAbortType(cocos2d::Ref* obj);
	void onChangeClassName(cocos2d::Ref* obj,ui::TextField::EventType type);
	void onCreateCode(cocos2d::Ref* ref);
	void onCloseInfo(cocos2d::Ref* ref);
	void updateInfo();
	void onOpenInfo(cocos2d::Ref* ref);
	void funcallback(float time);

	void CreateNode();
	void WriteFile();
	void GetChild(BtNode* node);

	ui::ScrollView* m_scroll;
	ui::Layout *m_bk;
	ui::Text *m_text;
	ui::ScrollView *m_scrInfo;
	ui::TextField *m_fileClassName;
	ui::Button *m_btnNodeType;
	ui::Button *m_btnAbortType;
	ui::Button *m_btnClose;
	ui::Button *m_btnOpen;

	tinyxml2::XMLDocument *m_pDoc;
	bool m_isClick;
};

#endif // __HELLOWORLD_SCENE_H__
