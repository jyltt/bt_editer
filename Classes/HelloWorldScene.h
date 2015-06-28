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
	void onCreateCode(cocos2d::Ref* ref);
	void funcallback(float time);

	void CreateNode();
	void WriteFile();
	void GetChild(BtNode* node);

	tinyxml2::XMLDocument *m_pDoc;
	ui::ScrollView* m_scroll;
	ui::Layout *m_bk;
	ui::Text *m_text;
	bool m_isClick;
};

#endif // __HELLOWORLD_SCENE_H__
