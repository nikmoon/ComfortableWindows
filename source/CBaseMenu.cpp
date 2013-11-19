/*
 * CBaseMenu.cpp
 *
 *  Created on: 18 ����. 2013 �.
 *      Author: karpachevnk
 */

#include "CBaseMenu.h"

namespace ComfortableWindows
{

/*
 *	�������� ����������� ����
 *	--------------------------------------
 */
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


/*
 *	���������� � ����� ���� ������-��������
 *	-----------------------------------------
 */
void
CBaseMenu::AddItemAtEnd(const string &_itext, const DWORD _actionid)
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


/*
 *	���������� � ����� ���� ������-�������
 *	-----------------------------------------
 */
void
CBaseMenu::AddItemAtEnd(const CSubMenu &_submenu)
{
	MENUITEMINFO mii;
	string mname = _submenu.GetName();

	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_TYPE | MIIM_SUBMENU;
	mii.fType = MFT_STRING;
	mii.dwTypeData = const_cast<LPTSTR>(mname.c_str());
	mii.cch = mname.length();
	mii.hSubMenu = _submenu.m_hMenu;
	::InsertMenuItem(m_hMenu, m_ItemCount, TRUE, &mii);

	m_ItemCount++;
}

/*
 *	���������� � ������ ���� ������-��������
 *	-----------------------------------------
 */
void
CBaseMenu::AddItemAtStart(const string &_itext, const DWORD _actionid)
{
	MENUITEMINFO mii;

	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_TYPE | MIIM_ID;
	mii.fType = MFT_STRING;
	mii.dwTypeData = const_cast<LPTSTR>(_itext.c_str());
	mii.cch = _itext.length();
	mii.wID = _actionid;
	::InsertMenuItem(m_hMenu, 0, TRUE, &mii);

	m_ItemCount++;
}


/*
 *	���������� � ������ ���� ������-�������
 *	-----------------------------------------
 */
void
CBaseMenu::AddItemAtStart(const CSubMenu &_submenu)
{
	MENUITEMINFO mii;
	string mname = _submenu.GetName();

	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_TYPE | MIIM_SUBMENU;
	mii.fType = MFT_STRING;
	mii.dwTypeData = const_cast<LPTSTR>(mname.c_str());
	mii.cch = mname.length();
	mii.hSubMenu = _submenu.m_hMenu;
	::InsertMenuItem(m_hMenu, 0, TRUE, &mii);

	m_ItemCount++;
}


/*
 *	����������� �������� ���� ����
 */
CMenuBar::CMenuBar(const CBaseWindow &_win) : CBaseMenu(EMT_MENUBAR)
{
	m_pWindow = &_win;
	::SetMenu(_win.GetHWnd(), m_hMenu);
};

} /* namespace ComfortableWindows */
