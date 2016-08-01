// author: wuming
#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class TipLayer;

class SaveDlg :
	public cocos2d::Layer
{
public:
	CREATE_FUNC(SaveDlg);
	virtual bool init();

	void SetTipsDlg(TipLayer* node);

private:
	void onSave(Ref* pSender);
	void onCancel(Ref* pSender);
	void ShowDlg(std::string name);
private:
	ui::TextField *m_labSaveName;
	ui::Button *m_btnSave;
	ui::Button *m_btnCancel;

	TipLayer* m_dlgTips=nullptr;
};
