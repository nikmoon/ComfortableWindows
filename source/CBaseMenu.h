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


/*
 *	“ипы меню
 *	------------------------------
 */
enum EMenuType : DWORD
{
	EMT_MENUBAR = 0,	// должен использоватьс€ только дл€ создани€ основного меню окна
	EMT_MENUDROPDOWN	// дл€ контекстного и вложенных меню
};


class CSubMenu;

/*
 *	Ѕазовый класс меню
 *	-------------------------------------
 */
class CBaseMenu
{
public:
	CBaseMenu(EMenuType _mtype);
	virtual ~CBaseMenu();

	void AddItemAtEnd(const string &_itext, DWORD _actionid);	// добавление пункта-действи€
	void AddItemAtStart(const string &_itext, DWORD _actionid);	// добавление пункта-действи€
	void AddItemAtEnd(const CSubMenu &_submenu);				// добавлени€ пункта-подменю
	void AddItemAtStart(const CSubMenu &_submenu);				// добавлени€ пункта-подменю

protected:
	HMENU m_hMenu;
	EMenuType m_MenuType;
	int m_ItemCount;
};

/*
 *	ѕодменю
 *	----------------------
 *
 *	¬сегда должно быть вложено в другое меню
 *	Ќе уничтожаетс€ €вно, т.к. уничтожаетс€ при уничтожении меню-родител€
 */
class CSubMenu : public CBaseMenu
{
public:
	CSubMenu(const string &_mname) : CBaseMenu(EMT_MENUDROPDOWN) { m_Name = _mname; };
	const string &GetName() const { return m_Name; };
private:
	string m_Name;
};

/*
 *	ќсновное меню приложени€
 *	---------------------------------------------
 */
class CMenuBar : public CBaseMenu
{
public:
	CMenuBar(const CBaseWindow &_win);

	void Update() { ::DrawMenuBar(m_pWindow->GetHWnd()); };

private:
	const CBaseWindow *m_pWindow;
};


/*
 *	 онтекстное меню
 *	----------------------------------------------
 */
class CContextMenu : public CBaseMenu
{
public:
	CContextMenu() : CBaseMenu(EMT_MENUDROPDOWN) {};
	~CContextMenu() { ::DestroyMenu(m_hMenu); };

	void Display(int x, int y,const CBaseWindow &_win) { ::TrackPopupMenuEx(m_hMenu, 0, x, y, _win.GetHWnd(), NULL); };
};

} /* namespace ComfortableWindows */

#endif /* CBASEMENU_H_ */
