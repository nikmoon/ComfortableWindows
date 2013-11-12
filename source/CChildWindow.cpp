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
	HINSTANCE _hinst, const SWindowRect &_rect, LPVOID _pdata)
	: CBaseWindow(_clname, _style|WS_CHILD|m_VisibleOnCreate, _exstyle, _text, CheckParent(_parent), (HMENU)_id, _hinst, _rect, _pdata)
{
	m_ID = _id;
}

void
CChildWindow::AddActionIndex(WORD _ntfycode, int _aindex)
{
	SNotifyBindWithActionIndex bindAction;

	bindAction.m_NotifyCode = _ntfycode;
	bindAction.m_ActionIndex = _aindex;

	m_NtfyActionIndex.push_back(bindAction);
}


int
CChildWindow::aIndex(WORD _ntfycode)
{
	for(auto it = m_NtfyActionIndex.begin(); it != m_NtfyActionIndex.end(); it++)
	{
		if ((*it).m_NotifyCode == _ntfycode)
			return (*it).m_ActionIndex;
	}
	return -1;
}



} /* namespace ComfortableWindows */
