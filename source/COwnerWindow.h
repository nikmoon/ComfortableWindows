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


//
//	Все возможные стили окон верхнего уровня
//
enum ETopLevelWindowStyle
{
	ETLWS_RECT = WS_POPUP,
	ETLWS_RECTWITH_BORDER = WS_POPUP|WS_BORDER,
	ETLWS_RECTWITH_SIZEBOX = WS_POPUP|WS_BORDER|WS_SIZEBOX,
	ETLWS_RECTWITH_CAPTION = WS_POPUP|WS_CAPTION,
	ETLWS_WINDOW_FIXED = WS_OVERLAPPED|WS_SYSMENU,
	ETLWS_WINDOW_FIXED_WITH_MINBUTT = WS_OVERLAPPED|WS_SYSMENU|WS_MINIMIZEBOX,
	ETLWS_WINDOW_FIXED_WITH_MAXBUTT = WS_OVERLAPPED|WS_SYSMENU|WS_MAXIMIZEBOX,
	ETLWS_WINDOW_FIXED_WITH_MINMAXBUTT = WS_OVERLAPPED|WS_SYSMENU|WS_MAXIMIZEBOX|WS_MINIMIZEBOX,
	ETLWS_WINDOW_SIZIBLE = WS_OVERLAPPED|WS_SYSMENU|WS_SIZEBOX,
	ETLWS_WINDOW_SIZIBLE_WITH_MINBUTT = WS_OVERLAPPED|WS_SYSMENU|WS_SIZEBOX|WS_MINIMIZEBOX,
	ETLWS_WINDOW_SIZIBLE_WITH_MAXBUTT = WS_OVERLAPPED|WS_SYSMENU|WS_SIZEBOX|WS_MAXIMIZEBOX,
	ETLWS_WINDOW_SIZIBLE_WITH_MINMAXBUTT = WS_OVERLAPPEDWINDOW
};


class COwnerWindow : public CBaseWindow
{
public:
	COwnerWindow(LPCTSTR _clname, ETopLevelWindowStyle _style, DWORD _exstyle, LPCTSTR _title, CBaseWindow *_parent, HMENU _hmenu,
			HINSTANCE _hinst, const SWindowRect &_rect, LPVOID _pdata = NULL);

	COwnerWindow(ETopLevelWindowStyle _style, DWORD _exstyle, LPCTSTR _title, CBaseWindow *_parent, HMENU _hmenu,
			HINSTANCE _hinst, const SWindowRect &_rect, LPVOID _pdata = NULL);

	virtual ~COwnerWindow();

	virtual LRESULT OnMessage(UINT msg, WPARAM wp, LPARAM lp);
	virtual LRESULT OnDestroy() = 0;
	virtual LRESULT ExecuteAction(int _aindex, UINT _msg, WPARAM wp, LPARAM lp);


private:
	bool m_IsStdWndClass;

	static UINT m_StdWndClassStyle;		// дефолтный стиль стандартного окна
	static WNDCLASSEX *m_StdWndClass;	// дефолтный оконный класс
	static int m_StdWndCount;			// количество созданных окон дефолтного класса
	static LPCTSTR RegisterStdWndClass(HINSTANCE _hinst);
	static void UnregisterStdWndClass();

};

} /* namespace ComfortableWindows */

#endif /* COWNERWINDOW_H_ */
