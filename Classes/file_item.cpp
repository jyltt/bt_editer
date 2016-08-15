// author: wuming
#include "file_item.h"
#include "cocostudio/CocoStudio.h"
#include "bt_node_manager.h"
#include "open_dlg.h"

FileItem::FileItem()
{
	setContentSize(Size(150, 50));
	auto root = CSLoader::createNode("file_item.csb");
	addChild(root);

	auto panel = (ui::Layout*)root->getChildByName("panel");
	m_btnDelete = (ui::Button*)panel->getChildByName("btn_delete");
	m_btnDelete->addClickEventListener(CC_CALLBACK_1(FileItem::onDelete, this));
	m_btn = (ui::Button*)panel->getChildByName("btn");
	m_btn->addClickEventListener(CC_CALLBACK_1(FileItem::onSelect, this));
}

void FileItem::SetAttr(FileInfo *info)
{
	m_info = info;
	m_btn->setTitleText(m_info->fileName);
}

void FileItem::onDelete(Ref* pSender)
{
	if (m_funcDelete)
		m_funcDelete(m_info);
}

void FileItem::onSelect(Ref* pSender)
{
	BtNodeManager::getSingleton().ClearNode();
	if (m_funcOpen)
		m_funcOpen(m_info);
}

void FileItem::SetOpenFileFunc(std::function<void(FileInfo*)> func)
{
	m_funcOpen = func;
}

void FileItem::SetDeleteFileFunc(std::function<void(FileInfo*)> func)
{
	m_funcDelete = func;
}

FileItem::~FileItem()
{

}