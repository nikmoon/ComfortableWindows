/*
 * CDialogWindow.h
 *
 *  Created on: 11 нояб. 2013 г.
 *      Author: karpachevnk
 */

#ifndef CDIALOGWINDOW_H_
#define CDIALOGWINDOW_H_

#include "CBaseWindow.h"
#include <string>

using namespace std;

namespace ComfortableWindows
{

//
//	Все возможные стили окон диалога
//
enum EDialogWindowStyle : DWORD
{
	EDWS_RECT = WS_POPUP,
	EDWS_RECTWITH_BORDER = WS_POPUP|WS_BORDER,
	EDWS_RECTWITH_SIZEBOX = WS_POPUP|WS_BORDER|WS_SIZEBOX,
	EDWS_RECTWITH_CAPTION = WS_POPUP|WS_CAPTION,
	EDWS_WINDOW_FIXED = WS_OVERLAPPED|WS_SYSMENU,
	EDWS_WINDOW_FIXED_WITH_MINBUTT = WS_OVERLAPPED|WS_SYSMENU|WS_MINIMIZEBOX,
	EDWS_WINDOW_FIXED_WITH_MAXBUTT = WS_OVERLAPPED|WS_SYSMENU|WS_MAXIMIZEBOX,
	EDWS_WINDOW_FIXED_WITH_MINMAXBUTT = WS_OVERLAPPED|WS_SYSMENU|WS_MAXIMIZEBOX|WS_MINIMIZEBOX,
	EDWS_WINDOW_SIZIBLE = WS_OVERLAPPED|WS_SYSMENU|WS_SIZEBOX,
	EDWS_WINDOW_SIZIBLE_WITH_MINBUTT = WS_OVERLAPPED|WS_SYSMENU|WS_SIZEBOX|WS_MINIMIZEBOX,
	EDWS_WINDOW_SIZIBLE_WITH_MAXBUTT = WS_OVERLAPPED|WS_SYSMENU|WS_SIZEBOX|WS_MAXIMIZEBOX,
	EDWS_WINDOW_SIZIBLE_WITH_MINMAXBUTT = WS_OVERLAPPEDWINDOW
};


class CDialogWindow : public CBaseWindow
{
public:
	CDialogWindow(EDialogWindowStyle _style, DWORD _exstyle, LPCTSTR _title, CBaseWindow *_parent, HMENU _hmenu,
			HINSTANCE _hinst, const SWindowRect &_rect);
	~CDialogWindow();

protected:
	virtual LRESULT OnCommand(UINT msg, WPARAM wp, LPARAM lp);

private:
	static int sm_DlgWndCount;
	LPCTSTR GetDlgWndClsName(HINSTANCE _hinst);
};

} /* namespace ComfortableWindows */

#endif /* CDIALOGWINDOW_H_ */
