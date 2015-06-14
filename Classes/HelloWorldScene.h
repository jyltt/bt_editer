#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <list>
#include "bt_Node.h"

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
	void getAllChild(cocos2d::Node* parent,bool write_file = true);
	void WriteFile(cocos2d::Node* parent, cocos2d::Node* child);
	std::list<BtNode*> m_list;
	struct Line
	{
		Line(cocos2d::Vec2 a1, cocos2d::Vec2 b1)
		{
			a = a1;
			b = b1;
		}
		cocos2d::Vec2 b;
		cocos2d::Vec2 a;
	};
	std::list<Line> m_rect;
	cocos2d::Node* root;
	std::string file;
};

#endif // __HELLOWORLD_SCENE_H__
