/*
 * CDialogWindow.cpp
 *
 *  Created on: 11 но€б. 2013 г.
 *      Author: karpachevnk
 */

#include <typeinfo>
#include "CDialogWindow.h"


namespace ComfortableWindows
{


CDialogWindow::	CDialogWindow(ETopLevelWindowStyle _style, DWORD _exstyle, LPCTSTR _title, CBaseWindow *_parent, HMENU _hmenu,
	HINSTANCE _hinst, SWindowRect &_rect, LPVOID _pdata)
	: COwnerWindow(_style, _exstyle, _title, _parent, _hmenu, _hinst, _rect, _pdata)
{
	// TODO Auto-generated constructor stub

}


LRESULT
CDialogWindow::OnMessage(UINT msg, WPARAM wp, LPARAM lp)
{
	LRESULT result;

	switch (msg)
	{
		case WM_COMMAND:
			if (lp != 0)	// если не нуль, значит уведомление от элемента управлени€
			{
				result = OnCommandFromControl((CControlWindow*)(GetWndPtr((HWND)lp)), HIWORD(wp));
			}
			else
			{
				result = CBaseWindow::OnMessage(msg,wp,lp);
			}
			break;
		default:
			result = CBaseWindow::OnMessage(msg,wp,lp);
			break;
	}

	return result;
}


LRESULT
CDialogWindow::OnCommandFromControl(CControlWindow *pwin, DWORD _ncode)
{
	if (typeid(*pwin) == typeid(CButton))
		return OnCommandFromButton(dynamic_cast<CButton*>(pwin), _ncode);
	if (typeid(*pwin) == typeid(CCheckBox))
		return OnCommandFromCheckbox(dynamic_cast<CCheckBox*>(pwin), _ncode);

	return 0;
}


LRESULT
CDialogWindow::OnCommandFromButton(CButton *pb, DWORD _ncode)
{
	return 0;
}


LRESULT
CDialogWindow::OnCommandFromCheckbox(CCheckBox *chb, DWORD _ncode)
{
	return 0;
}


} /* namespace ComfortableWindows */
