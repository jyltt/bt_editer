#ifndef ATTR_ITEM_H_
#define ATTR_ITEM_H_

#include "cocos2d.h"
#include "struct.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class AttrItem
	:public ui::Widget
{
public:
	CREATE_FUNC(AttrItem);
	AttrItem();
	~AttrItem();
	void SetAttr(Attr *data);
protected:
	void UpdateInfo();
	void onChangeValue(Ref *ref, ui::TextField::EventType type);

	Attr *m_Attr;
	ui::Text *m_Text;
	ui::TextField *m_Value;
	Node *m_RootNode;
private:
};

#endif