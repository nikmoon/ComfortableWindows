/*
 * CBaseWindow.cpp
 *
 *  Created on: 05 ����. 2013 �.
 *      Author: karpachevnk
 */

#include "CBaseWindow.h"

namespace ComfortableWindows
{


DWORD
CBaseWindow::sm_VisibleOnCreate = WS_VISIBLE;

//
//		�������� ����������� ������
//		-----------------------------------------------------
//
CBaseWindow::CBaseWindow(
	LPCTSTR _clname,		// ��� �������� ������
	DWORD _style,			// �������� ����� ��� ����
	DWORD _exstyle,			// ����������� ����� ��� ����
	LPCTSTR _title,			// ��������� ����
	CBaseWindow *_parent,	// ������������ ����
	HMENU _hmenu,			// ��������� ���� ����
	HINSTANCE _hinst,		// ��������� ������, ���������� ����
	const SWindowRect &_rect,	// ��������� ����
	LPVOID _pdata)			// �������������� ������ ��� �������� ����
{
	// ������� ��������� ������������� ����
	HWND hparent = (_parent == NULL) ? NULL : _parent->m_hWnd;

	// ���� ����� �������, ���� ���� �� ���� �� ������ ����������
	_style |= sm_VisibleOnCreate;

	// �������� ����
	m_hWnd = ::CreateWindowEx(_exstyle, _clname, _title, _style, _rect.x, _rect.y, _rect.cx, _rect.cy, hparent, _hmenu, _hinst, _pdata);
	// �������� �� ������
	if (m_hWnd == NULL)
	{
		// ����� ������� ����������
	}

	// �������������� ��������� ���� ����������
	m_hInst = _hinst;
	m_ClassName = _clname;
	m_pParent = _parent;

	// ��������� ���������� ������� ���������� � ��������� ��������� �����
	Binding(m_hWnd);
}


//
//		����������
//		----------------------------------
//
CBaseWindow::~CBaseWindow()
{
	// ���� �� ������ ����������� ���������� ���� ��� �� ����������
	if (::IsWindow(m_hWnd))
	{
		// �������������
		::MessageBox(NULL, "��������� ������������, �� ���� ����������", "��������", MB_OK);

		// ���������� ����������
	}
}


//
//		��������� ���������� ���������
//
//		���������� � ������ ���������� ������-���� �����������
//		��� ������������� ����� ����������������
//
LRESULT
CBaseWindow::OnMessageDefault(UINT msg, WPARAM wp, LPARAM lp)
{
	return ::DefWindowProc(m_hWnd, msg, wp, lp);
};


//
//		������� ���������� ���������
//
//		���������������� ��� ����������� �������
//
LRESULT
CBaseWindow::OnMessage(UINT msg, WPARAM wp, LPARAM lp)
{
	LRESULT result;

	switch (msg)
	{
		case WM_PAINT:
			result = OnPaint(msg,wp,lp);
			break;
		case WM_DESTROY:
			result = OnDestroy(msg,wp,lp);
			break;
		case WM_COMMAND:
			result = OnCommand(msg,wp,lp);
			break;
		default:
			result = OnMessageDefault(msg,wp,lp);
			break;
	}
	return result;
}


LRESULT
CBaseWindow::OnPaint(UINT msg, WPARAM wp, LPARAM lp)
{
	return OnMessageDefault(msg,wp,lp);
}


LRESULT
CBaseWindow::OnDestroy(UINT msg, WPARAM wp, LPARAM lp)
{
	return OnMessageDefault(msg,wp,lp);
}


LRESULT
CBaseWindow::OnCommand(UINT msg, WPARAM wp, LPARAM lp)
{
	return OnMessageDefault(msg,wp,lp);
}


LRESULT
CBaseWindow::ExecuteAction(int _aindex, UINT _msg, WPARAM _wp, LPARAM _lp)
{
	return OnMessageDefault(_msg,_wp,_lp);
}



int
CBaseWindow::GetActionIndex(WORD _ntfy)
{
	// ���� ������� � ��������� ����� �����������
	for (SNotifyBindWithActionIndex &s : m_NtfyActionIndexArray)
	{
		if (s.m_NotifyCode == _ntfy)	// ������ ����� �������
			return s.m_ActionIndex;
	}

	// ������� �� ������
	return -1;
}

void
CBaseWindow::SetActionIndex(WORD _ntfy, int _aindex)
{
	// ������� ��������� ����� ������� � ��������� ����� �����������
	for (SNotifyBindWithActionIndex &s : m_NtfyActionIndexArray)
	{
		if (s.m_NotifyCode == _ntfy)	// ������ ����� �������
		{
			s.m_ActionIndex = _aindex;	// ���������� ������ ��������
			return;		// �����
		}
	}

	// ������� �� ������, �������
	m_NtfyActionIndexArray.push_back( {_ntfy,_aindex} );
}


LRESULT CALLBACK
CBaseWindow::BaseWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	// �������� ����� ���������� � ����� ���������� �������
	CBaseWindow * pWindow = CBaseWindow::GetObjectPtr(hwnd);

	return (pWindow) ? pWindow->OnMessage(msg, wp, lp) : ::DefWindowProc(hwnd, msg, wp, lp);
}


} /* namespace ComfortableWindows */
