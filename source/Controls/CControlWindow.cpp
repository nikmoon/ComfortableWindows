/*
 * CControlWindow.cpp
 *
 *  Created on: 08 но€б. 2013 г.
 *      Author: karpachevnk
 */

#include "CControlWindow.h"

namespace ComfortableWindows
{

DWORD
CControlWindow::m_BeginGroup = WS_GROUP|WS_TABSTOP;


CControlWindow::CControlWindow(LPCTSTR _clname, DWORD _style, DWORD _exstyle, LPCTSTR _text, CBaseWindow *_parent, UINT _id,
	HINSTANCE _hinst, SWindowRect &_rect)
	: CChildWindow(_clname,_style|m_BeginGroup,_exstyle,_text,_parent,_id,_hinst,_rect,NULL)
{
	// если текущий элемент стал началом группы, флаг надо сбросить
	m_BeginGroup ^= m_BeginGroup;
}


} /* namespace ComfortableWindows */
