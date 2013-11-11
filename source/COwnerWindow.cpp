/*
 * COwnerWindow.cpp
 *
 *  Created on: 06 ����. 2013 �.
 *      Author: karpachevnk
 */

#include "COwnerWindow.h"

namespace ComfortableWindows
{

// ����� ������������ ����
UINT
COwnerWindow::m_StdWndClassStyle = CS_HREDRAW|CS_VREDRAW;

// ����������� ����� ��� ����
WNDCLASSEX *
COwnerWindow::m_StdWndClass = NULL;

// ���������� ���� ������������ ������
int
COwnerWindow::m_StdWndCount = 0;


LPCTSTR
COwnerWindow::RegisterStdWndClass(HINSTANCE _hinst)
{
	// ���� ����������� ����� ��� �� ���������������, ������������
	if (m_StdWndClass == NULL)
	{
		m_StdWndClass = new WNDCLASSEX;

		m_StdWndClass->cbSize = sizeof(WNDCLASSEX);
		m_StdWndClass->cbClsExtra = 0;
		m_StdWndClass->cbWndExtra = 0;
		m_StdWndClass->style = m_StdWndClassStyle;
		m_StdWndClass->hInstance = _hinst;
		m_StdWndClass->lpfnWndProc = &CBaseWindow::BaseWndProc;
		m_StdWndClass->lpszClassName = "CStdWindowClass";
		m_StdWndClass->hCursor = ::LoadCursor(NULL,IDC_ARROW);
		m_StdWndClass->hIcon = ::LoadIcon(NULL,IDI_APPLICATION);
		m_StdWndClass->hIconSm = ::LoadIcon(NULL,IDI_APPLICATION);
		m_StdWndClass->hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		m_StdWndClass->lpszMenuName = NULL;

		// �������� ���������������� ������� �����
		if (::RegisterClassEx(m_StdWndClass) == 0)
		{	// ���� ���������� ����������
			throw(1);
		}
	}

	// �������������� ������� ���� ������������ ������
	m_StdWndCount++;

	return m_StdWndClass->lpszClassName;
}


void
COwnerWindow::UnregisterStdWndClass()
{
	// �������������� ������� ���� ������������ ������
	m_StdWndCount--;

	// ���� ���� ������ ���
	if (m_StdWndCount == 0)
	{	// �������� ��������� ����������� ������
		if (::UnregisterClass(m_StdWndClass->lpszClassName, m_StdWndClass->hInstance) == 0)
		{	// �����-�� ������, ���������� ����������
			throw(1);
		}

		delete m_StdWndClass;	// ������� ��������� �� ������
		m_StdWndClass = NULL;	// �������� ���������
	}
}




COwnerWindow::COwnerWindow(LPCTSTR _clname, ETopLevelWindowStyle _style, DWORD _exstyle, LPCTSTR _title, CBaseWindow *_parent, HMENU _hmenu,
	HINSTANCE _hinst, SWindowRect &_rect, LPVOID _pdata)
	: CBaseWindow(_clname, _style, _exstyle, _title, _parent, _hmenu, _hinst, _rect, _pdata)
{	// ���� ������� �� ������ ����������������� �������� ������
	m_IsStdWndClass = false;
}



COwnerWindow::COwnerWindow(ETopLevelWindowStyle _style, DWORD _exstyle, LPCTSTR _title, CBaseWindow *_parent, HMENU _hmenu,
	HINSTANCE _hinst, SWindowRect &_rect, LPVOID _pdata)
	: CBaseWindow(RegisterStdWndClass(_hinst), _style, _exstyle, _title, _parent, _hmenu, _hinst, _rect, _pdata)
{	// ���� ������� �� ������ ������������ �������� ������
	m_IsStdWndClass = true;
}


COwnerWindow::~COwnerWindow()
{
	// ���� ���� ������������ ������
	if (m_IsStdWndClass)
	{	// �������� ������ �������� ����������� ������������ ������
		UnregisterStdWndClass();
	}
}



LRESULT
COwnerWindow::OnMessage(UINT msg, WPARAM wp, LPARAM lp)
{
	LRESULT result;

	result = CBaseWindow::OnMessage(msg,wp,lp);

	return result;
}


} /* namespace ComfortableWindows */
