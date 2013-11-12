/*
 * CBaseWindow.cpp
 *
 *  Created on: 05 ����. 2013 �.
 *      Author: karpachevnk
 */

#include "CBaseWindow.h"

namespace ComfortableWindows
{


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

	// �������� ����
	m_hWnd = ::CreateWindowEx(_exstyle, _clname, _title, _style, _rect.x, _rect.y, _rect.cx, _rect.cy, hparent, _hmenu, _hinst, _pdata);
	// �������� �� ������
	if (m_hWnd == NULL)
	{
		// ����� ������� ����������
	}

	// ��������� ���������� ������� ���������� � ��������� ��������� �����
	Binding(m_hWnd, this);

	// �������������� ��������� ���� ����������
	m_hInst = _hinst;
	m_ClassName = _clname;
	m_pParent = _parent;
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
	return OnMessageDefault(msg, wp, lp);
}


LRESULT CALLBACK
CBaseWindow::BaseWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	// �������� ����� ���������� � ����� ���������� �������
	CBaseWindow * pWindow = CBaseWindow::GetObjectPtr(hwnd);

	return (pWindow) ? pWindow->OnMessage(msg, wp, lp) : ::DefWindowProc(hwnd, msg, wp, lp);
}


} /* namespace ComfortableWindows */
