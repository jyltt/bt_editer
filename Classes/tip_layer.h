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

private:
	void HideDlg();
	void onClickBackground(Ref* pSender);
private:
	ui::Text *m_labDes;
	ui::Layout* m_layBk;
};
