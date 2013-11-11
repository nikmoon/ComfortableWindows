/*
 * COwnerWindow.h
 *
 *  Created on: 06 нояб. 2013 г.
 *      Author: karpachevnk
 */

#ifndef COWNERWINDOW_H_
#define COWNERWINDOW_H_

#include "CBaseWindow.h"


namespace ComfortableWindows
{


// все возможные стили окон верхнего уровня
enum ETopLevelWindowStyle
{
	TLWS_RECT = WS_POPUP,
	TLWS_RECTWITH_BORDER = WS_POPUP|WS_BORDER,
	TLWS_RECTWITH_SIZEBOX = WS_POPUP|WS_BORDER|WS_SIZEBOX,
	TLWS_RECTWITH_CAPTION = WS_POPUP|WS_CAPTION,
	TLWS_WINDOW_FIXED = WS_OVERLAPPED|WS_SYSMENU,
	TLWS_WINDOW_FIXED_WITH_MINBUTT = WS_OVERLAPPED|WS_SYSMENU|WS_MINIMIZEBOX,
	TLWS_WINDOW_FIXED_WITH_MAXBUTT = WS_OVERLAPPED|WS_SYSMENU|WS_MAXIMIZEBOX,
	TLWS_WINDOW_FIXED_WITH_MINMAXBUTT = WS_OVERLAPPED|WS_SYSMENU|WS_MAXIMIZEBOX|WS_MINIMIZEBOX,
	TLWS_WINDOW_SIZIBLE = WS_OVERLAPPED|WS_SYSMENU|WS_SIZEBOX,
	TLWS_WINDOW_SIZIBLE_WITH_MINBUTT = WS_OVERLAPPED|WS_SYSMENU|WS_SIZEBOX|WS_MINIMIZEBOX,
	TLWS_WINDOW_SIZIBLE_WITH_MAXBUTT = WS_OVERLAPPED|WS_SYSMENU|WS_SIZEBOX|WS_MAXIMIZEBOX,
	TLWS_WINDOW_SIZIBLE_WITH_MINMAXBUTT = WS_OVERLAPPEDWINDOW
};


class COwnerWindow : public CBaseWindow
{
public:
	COwnerWindow(LPCTSTR _clname, ETopLevelWindowStyle _style, DWORD _exstyle, LPCTSTR _title, CBaseWindow *_parent, HMENU _hmenu,
			HINSTANCE _hinst, SWindowRect &_rect, LPVOID _pdata = NULL);

	COwnerWindow(ETopLevelWindowStyle _style, DWORD _exstyle, LPCTSTR _title, CBaseWindow *_parent, HMENU _hmenu,
			HINSTANCE _hinst, SWindowRect &_rect, LPVOID _pdata = NULL);

	virtual ~COwnerWindow();

	virtual LRESULT OnMessage(UINT msg, WPARAM wp, LPARAM lp);

private:
	bool m_IsStdWndClass;

	static UINT m_StdWndClassStyle;
	static WNDCLASSEX *m_StdWndClass;
	static int m_StdWndCount;
	static LPCTSTR RegisterStdWndClass(HINSTANCE _hinst);
	static void UnregisterStdWndClass();

};

} /* namespace ComfortableWindows */

#endif /* COWNERWINDOW_H_ */
