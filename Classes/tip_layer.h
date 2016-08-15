// author: wuming
#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class TipLayer:
	public cocos2d::Layer
{
public:
	CREATE_FUNC(TipLayer);
	virtual bool init();

	void ShowDlg(std::string des);
	void ShowDlg(std::string des,std::function<void()> func_sure,std::function<void()> func_cancel = nullptr);

private:
	void HideDlg();
	void onClickBackground(Ref* pSender);
	void onCancel(Ref* pSender);
	void onSure(Ref* pSender);
private:
	ui::Text *m_labDes;
	ui::Layout* m_layBk;
	ui::Button *m_btnCancel;
	ui::Button *m_btnSure;

	std::function<void()> m_funcSure = nullptr;
	std::function<void()> m_funcCancel = nullptr;
};
