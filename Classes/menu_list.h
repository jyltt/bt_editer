#ifndef MENU_LIST_H_
#define MENU_LIST_H_

#include "cocos2d.h"
#include "struct.h"
#include "enum.h"
#include <vector>
#include "ui/CocosGUI.h"

USING_NS_CC;
class HelloWorld;

class MenuList:
	public cocos2d::Node
{
public:
	CREATE_FUNC(MenuList);
	MenuList();
	~MenuList();

	void SetFileList(FileList *list);
	void SetNodeRoot(HelloWorld* node);
	CC_PROPERTY(bool, m_isShow, Show);
protected:
	ui::Button *CreateButton(std::string name);
	void updateUI();
	void onClick(Ref*obj);
private:
	HelloWorld* m_Root = nullptr;
	FileList *m_List = nullptr;
	MenuList *m_Child = nullptr;
	std::vector<ui::Button*> m_btnList;
};

#endif