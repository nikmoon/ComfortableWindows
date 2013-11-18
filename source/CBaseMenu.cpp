/*
 * CBaseMenu.cpp
 *
 *  Created on: 18 нояб. 2013 г.
 *      Author: karpachevnk
 */

#include "CBaseMenu.h"

namespace ComfortableWindows
{

CBaseMenu::CBaseMenu(EMenuType _mtype)
{
	switch (_mtype)
	{
		case EMT_MENUBAR:
			m_hMenu = ::CreateMenu();
			break;
		case EMT_MENUDROPDOWN:
			m_hMenu = ::CreatePopupMenu();
			break;
		default:
			m_hMenu = ::CreatePopupMenu();
			break;
	}
	m_MenuType = _mtype;
	m_ItemCount = 0;
}

CBaseMenu::~CBaseMenu()
{
	// TODO Auto-generated destructor stub
}


void
CBaseMenu::AddItem(const string &_itext, const DWORD _actionid)
{
	MENUITEMINFO mii;

	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_TYPE | MIIM_ID;
	mii.fType = MFT_STRING;
	mii.dwTypeData = const_cast<LPTSTR>(_itext.c_str());
	mii.cch = _itext.length();
	mii.wID = _actionid;
	::InsertMenuItem(m_hMenu, m_ItemCount, TRUE, &mii);

	m_ItemCount++;
}

void
CBaseMenu::AddItem(const string &_itext, const CBaseMenu *_psubmenu)
{
	if (_psubmenu == NULL)
	{
		// исключение генерим
		return;
	}

	MENUITEMINFO mii;

	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_TYPE | MIIM_SUBMENU;
	mii.fType = MFT_STRING;
	mii.dwTypeData = const_cast<LPTSTR>(_itext.c_str());
	mii.cch = _itext.length();
	mii.hSubMenu = _psubmenu->m_hMenu;
	::InsertMenuItem(m_hMenu, m_ItemCount, TRUE, &mii);

	m_ItemCount++;
}



CMenuBar::CMenuBar(const CBaseWindow &_win) : CBaseMenu(EMT_MENUBAR)
{
	m_pWindow = &_win;
	::SetMenu(_win.GetHWnd(), m_hMenu);
};

} /* namespace ComfortableWindows */
