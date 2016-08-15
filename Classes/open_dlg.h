// author: wuming
#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class TipLayer;
class FileItem;
struct FileInfo
{
	std::string fileName;
	std::string path;
};

class OpenDlg:
	public cocos2d::Layer
{
public:
	CREATE_FUNC(OpenDlg);
	virtual bool init();

	void SetTipsDlg(TipLayer* node);
	void SetOpenFileFunc(std::function<void(std::string)> func);
	void UpdateItem();
private:
	void GetDoc(std::string filepath);
	void onClick(Ref* pSender);
	void onCancel(Ref* pSender);
	void ShowDlg(std::string name);
private:
	ui::Button *m_btnCancel;
	ui::ListView *m_list;
	std::vector<FileItem*> m_btnList;

	TipLayer* m_dlgTips = nullptr;
	std::vector<FileInfo*> m_fileList;
	std::function<void(std::string)> m_funcOpen;
};
