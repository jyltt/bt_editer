#include "menu_list.h"
#include "Tools.h"
#include "HelloWorldScene.h"
#include "read_file.h"

MenuList::MenuList()
{ }

void MenuList::SetFileList(FileList *list)
{
	m_List = list;
	updateUI();
}

void MenuList::setShow(bool var)
{
	m_isShow = var;
	setVisible(var);
	if (var)
	{
		updateUI();
	}
}

bool MenuList::getShow()
{
	return m_isShow;
}

void MenuList::updateUI()
{
	for (auto btn:m_btnList)
	{
		btn->setVisible(false);
		btn->removeFromParent();
	}
	m_btnList.clear();
	for (auto doc:m_List->docListName)
	{
		std::string name = doc+"  =>";
		auto btn = CreateButton(name);
		btn->setUserData(m_List->FindDoc(doc));
		addChild(btn);
	}
	for (int i = 0; i<m_List->fileList.size();i++)
	{
		auto path = m_List->fileList[i];
		std::string name = Tools::FormPathToName(path);
		auto btn = CreateButton(name);
		btn->setTag(i);
		addChild(btn);
	}
}

ui::Button *MenuList::CreateButton(std::string name)
{
	auto btn = ui::Button::create("Default/Button_Normal.png");
	m_btnList.push_back(btn);
	btn->addClickEventListener(CC_CALLBACK_1(MenuList::onClick, this));
	btn->setTitleText(name);
	btn->setTitleColor(Color3B(0, 0, 0));
	btn->setScale9Enabled(true);
	btn->setContentSize(Size(100, 20));
	btn->setPosition(Vec2(50, -22*(int)m_btnList.size()));
	return btn;
}

void MenuList::onClick(Ref*obj)
{
	auto btn = (ui::Button*)obj;
	std::string name = btn->getTitleText();
	if (name.find(" =>") != name.npos)
	{
		auto doc = (FileList*)btn->getUserData();
		if (m_Child == nullptr)
		{
			m_Child = new MenuList();
			m_Child->SetNodeRoot(m_Root);
			m_Child->setShow(false);
			addChild(m_Child);
		}
		if (m_Child->getShow())
			m_Child->setShow(false);
		else
		{
			auto pos = btn->getPosition();
			m_Child->setPosition(pos.x+52, pos.y+22);
			m_Child->SetFileList(doc);
			m_Child->setShow(true);
		}
	}
	else
	{
		int id = btn->getTag();
		auto path = m_List->fileList[id];
		auto name = Tools::FormPathToName(path);
		auto class_node = ReadFile::getSingleton().GetNodeClassInfo(name);
		//创建节点
		m_Root->SetNode(getPosition(),class_node);
	}
}

void MenuList::SetNodeRoot(HelloWorld* node)
{
	m_Root = node;
}

MenuList::~MenuList()
{ }