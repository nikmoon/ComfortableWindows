/*
 * CBaseMenu.h
 *
 *  Created on: 18 но€б. 2013 г.
 *      Author: karpachevnk
 */

#ifndef CBASEMENU_H_
#define CBASEMENU_H_

#include <windows.h>
#include <windowsx.h>
#include <string>
#include "CBaseWindow.h"


using namespace std;

namespace ComfortableWindows
{


enum EMenuType : DWORD
{
	EMT_MENUBAR = 0,
	EMT_MENUDROPDOWN
};


class CBaseMenu
{
public:
	CBaseMenu(EMenuType _mtype);
	virtual ~CBaseMenu();

	void AddItem(const string &_itext, DWORD _actionid);
	void AddItem(const string &_itext, const CBaseMenu *_psubmenu);

protected:
	HMENU m_hMenu;
	EMenuType m_MenuType;
	int m_ItemCount;
};


class CMenuBar : public CBaseMenu
{
public:
	CMenuBar(const CBaseWindow &_win);

	void Update() { ::DrawMenuBar(m_pWindow->GetHWnd()); };

private:
	const CBaseWindow *m_pWindow;
};



class CContextMenu : public CBaseMenu
{
public:
	CContextMenu() : CBaseMenu(EMT_MENUDROPDOWN) {};
	~CContextMenu() { ::DestroyMenu(m_hMenu); };

	void Display(int x, int y,const CBaseWindow &_win) { ::TrackPopupMenuEx(m_hMenu, 0, x, y, _win.GetHWnd(), NULL); };
};


class CSubMenu : public CBaseMenu
{
public:
	CSubMenu() : CBaseMenu(EMT_MENUDROPDOWN) {};
};

} /* namespace ComfortableWindows */

#endif /* CBASEMENU_H_ */
