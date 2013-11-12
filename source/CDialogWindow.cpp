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
	HINSTANCE _hinst, const SWindowRect &_rect, LPVOID _pdata)
	: COwnerWindow(_style, _exstyle, _title, _parent, _hmenu, _hinst, _rect, _pdata)
{

}


} /* namespace ComfortableWindows */
