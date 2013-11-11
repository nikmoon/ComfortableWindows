/*
 * CChildWindow.cpp
 *
 *  Created on: 07 но€б. 2013 г.
 *      Author: karpachevnk
 */

#include "CChildWindow.h"

namespace ComfortableWindows
{

DWORD
CChildWindow::m_VisibleOnCreate = WS_VISIBLE;


CChildWindow::CChildWindow(LPCTSTR _clname, DWORD _style, DWORD _exstyle, LPCTSTR _text, CBaseWindow *_parent, UINT _id,
	HINSTANCE _hinst, SWindowRect &_rect, LPVOID _pdata)
	: CBaseWindow(_clname, _style|WS_CHILD|m_VisibleOnCreate, _exstyle, _text, CheckParent(_parent), (HMENU)_id, _hinst, _rect, _pdata)
{
	m_ID = _id;
}


CChildWindow::~CChildWindow()
{
	// TODO Auto-generated destructor stub
}

} /* namespace ComfortableWindows */
