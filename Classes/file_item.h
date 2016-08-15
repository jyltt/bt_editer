// author: wuming
#ifndef FILE_ITEM_H_
#define FILE_ITEM_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

struct FileInfo;

class FileItem:
	public ui::Widget
{
public:
	CREATE_FUNC(FileItem);
	FileItem();
	~FileItem();
	void SetAttr(FileInfo *info);
	void SetOpenFileFunc(std::function<void(FileInfo*)> func);
	void SetDeleteFileFunc(std::function<void(FileInfo*)> func);
protected:
	void onSelect(Ref* pSender);
	void onDelete(Ref* pSender);
private:
	ui::Button *m_btn;
	ui::Button *m_btnDelete;
	std::function<void(FileInfo*)> m_funcOpen;
	std::function<void(FileInfo*)> m_funcDelete;
	FileInfo *m_info;
};

#endif // !file_item_h_
