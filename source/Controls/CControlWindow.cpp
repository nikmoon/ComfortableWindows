/*
 * CControlWindow.cpp
 *
 *  Created on: 08 но€б. 2013 г.
 *      Author: karpachevnk
 */

#include "CControlWindow.h"

namespace ComfortableWindows
{

SControlTypeInfo
CControlWindow::m_ControlClasses[]
{
		{"Button", BS_PUSHBUTTON},
		{"Button", BS_AUTOCHECKBOX|BS_PUSHLIKE},
		{"Button", BS_CHECKBOX},
		{"Button", BS_AUTOCHECKBOX},
		{"Button", BS_3STATE},
		{"Button", BS_AUTO3STATE}
};

DWORD
CControlWindow::m_BeginGroup = WS_GROUP|WS_TABSTOP;


CControlWindow::CControlWindow(EControlType _type, DWORD _exstyle, LPCTSTR _text, CBaseWindow *_parent, UINT _id,
	HINSTANCE _hinst, SWindowRect &_rect)
	: CChildWindow(m_ControlClasses[_type].m_CtrlClassName,m_ControlClasses[_type].m_CtrlStyle|m_BeginGroup,_exstyle,_text,_parent,_id,_hinst,_rect,NULL)
{	// если текущий элемент стал началом группы, флаг надо сбросить
	m_BeginGroup ^= m_BeginGroup;
}


} /* namespace ComfortableWindows */
