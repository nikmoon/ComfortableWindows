/*
 * CControlWindow.cpp
 *
 *  Created on: 08 ����. 2013 �.
 *      Author: karpachevnk
 */

#include "CControlWindow.h"

namespace ComfortableWindows
{

//
//		����, ������������ ������ ������� ������
//		���������� ��� ������� ���������� (�������� ������)
//		������������� ������������ ��� �������� ������ ��������
//
DWORD
CControlWindow::sm_BeginGroup = WS_GROUP|WS_TABSTOP;


CControlWindow::CControlWindow(
	LPCTSTR _clname,
	DWORD _style,
	DWORD _exstyle,
	LPCTSTR _text,
	CBaseWindow *_parent,
	UINT _id,
	HINSTANCE _hinst,
	const SWindowRect &_rect)
	: CBaseWindow(_clname,_style|WS_CHILD|sm_BeginGroup,_exstyle,_text,_parent,(HMENU)_id,_hinst,_rect,NULL)
{
	// ���� ������� ������� ���� ������� ������, ���� ���� ��������
	sm_BeginGroup ^= sm_BeginGroup;
}


} /* namespace ComfortableWindows */
