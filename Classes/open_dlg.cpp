// author: wuming
#include "open_dlg.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "bt_node_manager.h"
#include "xml_file.h"
#include "tip_layer.h"
#ifndef WIN32
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#else
#include <io.h>
#endif

using namespace cocostudio;

bool OpenDlg::init()
{
	if (!Layer::init())
		return false;

	auto _root = CSLoader::createNode("open_dlg.csb");
	addChild(_root);

	auto panel = (ui::Layout*)_root->getChildByName("Panel_1");
	m_btnCancel = (ui::Button*)panel->getChildByName("bt_cancel");
	m_btnCancel->addClickEventListener(CC_CALLBACK_1(OpenDlg::onCancel, this));
	m_list = (ui::ListView *)panel->getChildByName("list");

	GetDoc("cfg/");
	for (auto item:m_fileList)
	{
		//auto btn = ui::Button::create("Button_Normal.png");
		auto btn = (ui::Button*)m_btnCancel->clone();
		btn->setUserData(item);
		btn->setContentSize(Size(150, 50));
		btn->addClickEventListener(CC_CALLBACK_1(OpenDlg::onClick, this));
		btn->setTitleText(item->fileName);
		m_list->pushBackCustomItem(btn);
		m_btnList.push_back(btn);
	}
	m_list->refreshView();

	return true;
}

void OpenDlg::UpdateItem()
{
}

void OpenDlg::onClick(Ref* pSender)
{
	auto btn = (ui::Button*)pSender;
	auto info = (FileInfo*)btn->getUserData();
}

void OpenDlg::ShowDlg(std::string name)
{
	m_dlgTips->ShowDlg(name);
}

void OpenDlg::SetTipsDlg(TipLayer* node)
{
	m_dlgTips = node;
}

void OpenDlg::onCancel(Ref* pSender)
{
	setVisible(false);
}
#ifndef WIN32
void OpenDlg::GetDoc(std::string filepath)
{
	DIR *dir;
	if (!(dir = opendir(filepath.c_str())))
	{
		return;
	}
	dirent *d_ent;
	char fullpath[128];
	while ((d_ent = readdir(dir)) != NULL)
	{
		struct stat file_stat;
		if (strncmp(d_ent->d_name, ".", 1) == 0)
		{
			continue;   // 忽略"."目录
		}
		memset(fullpath, '\0', sizeof(fullpath));
		strcpy(fullpath, filepath.c_str());
		if (!strcmp(fullpath, "/"))
		{
			fullpath[0] = '\0';
		}
		strcat(fullpath, "/");
		strcat(fullpath, d_ent->d_name);
		if (lstat(fullpath, &file_stat) < 0)
		{
			return;
		}
		if ((d_ent->d_type&DT_DIR) != 0)
		{
			GetDoc(filepath+d_ent->d_name+"/");
		}
		else
		{
			if (strstr(d_ent->d_name, ".xml"))
			{
				auto file_info = new FileInfo();
				file_info->fileName = d_ent->d_name;
				file_info->path = filepath + d_ent->d_name;
				m_fileList.push_back(file_info);
			}
		}
	}
	closedir(dir);
}
#else
void OpenDlg::GetDoc(std::string filepath)
{
	_finddata_t file;
	auto path = filepath+"*.*";
	long lf;
	if ((lf = _findfirst(path.c_str(), &file))!=-1)
	{
		while (_findnext(lf, &file)==0)
		{
			if (strcmp(file.name, "..")==0) continue;
			auto b = file.attrib&_A_SUBDIR;
			if ((file.attrib&_A_SUBDIR) != 0)
			{
				GetDoc(filepath+file.name+"/");
			}
			else
			{
				if (strstr(file.name, ".xml"))
				{
					auto file_info = new FileInfo();
					file_info->fileName = file.name;
					file_info->path = filepath + file.name;
					m_fileList.push_back(file_info);
				}
			}
		}
	}
	_findclose(lf);
}
#endif