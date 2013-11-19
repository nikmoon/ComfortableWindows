/*
 * CDialogWindow.cpp
 *
 *  Created on: 11 ����. 2013 �.
 *      Author: karpachevnk
 */

#include "CDialogWindow.h"


namespace ComfortableWindows
{

// ������� ����� ����� ��������� ���������� ����
int
CDialogWindow::sm_DlgWndCount = 0;


LPCTSTR
CDialogWindow::GetDlgWndClsName(HINSTANCE _hinst)
{
	static LPCTSTR clname = "CDlgWndCls";

	// ��������, ��������������� �� ����� ����������� ����
	if (sm_DlgWndCount == 0)	// �� ���������������
	{
		// ������������ ����� ����������� ����
		WNDCLASSEX wc;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.style = CS_HREDRAW|CS_VREDRAW;
		wc.hInstance = _hinst;
		wc.lpfnWndProc = &CBaseWindow::BaseWndProc;
		wc.lpszClassName = clname;
		wc.hCursor = ::LoadCursor(NULL,IDC_ARROW);
		wc.hIcon = ::LoadIcon(NULL,IDI_APPLICATION);
		wc.hIconSm = ::LoadIcon(NULL,IDI_APPLICATION);
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wc.lpszMenuName = NULL;

		// �������� ���������������� ������� �����
		if (::RegisterClassEx(&wc) == 0)
		{	// ���� ���������� ����������
			throw(1);
		}

	}

	++sm_DlgWndCount;	// ����������� ������� ���������� ����
	return clname;
}


CDialogWindow::	CDialogWindow(
	EDialogWindowStyle _style,
	DWORD _exstyle,
	LPCTSTR _title,
	CBaseWindow *_parent,
	HMENU _hmenu,
	HINSTANCE _hinst,
	const SWindowRect &_rect)
	: CBaseWindow(GetDlgWndClsName(_hinst),_style,_exstyle,_title,_parent,_hmenu,_hinst,_rect)
{
}


CDialogWindow::~CDialogWindow()
{
	// ��������� ������� ���������� ����
	--sm_DlgWndCount;

	// ���� ��� ���� ��������� ���������� ����
	if (sm_DlgWndCount == 0)
	{
		// �������� ����������� ������ ����������� ����
		::UnregisterClass(m_ClassName.c_str(),m_hInst);
	}
}


LRESULT
CDialogWindow::OnCommand(UINT msg, WPARAM wp, LPARAM lp)
{
	LRESULT result;

	//
	// ��������� ����������� �� �������� ����������
	// ---------------------------------------------------------
	//
	if (lp != 0)	// �������� ����������� �� ��������� ��������
	{
		CBaseWindow *pCtrl = CBaseWindow::GetObjectPtr((HWND)lp);	// �������� �������� �������
		if (pCtrl)
		{
			int aindex = pCtrl->GetActionIndex(HIWORD(wp));		// �������� �� ��������� �������� ����������� ������ ��������
			result = ExecuteAction(aindex,msg,wp,lp);	// ��������� ��������� ��������
		}
		else
		{
			result = OnMessageDefault(msg,wp,lp);
		}
	}
	//
	// ��������� ����������� �� ����
	// ---------------------------------------------------------
	//
	else if (HIWORD(wp) == 0)
	{
		result = ExecuteAction(LOWORD(wp),msg,wp,lp);	// ��������� ��������� �������� �� ����
	}
	else
	{
		result = OnMessageDefault(msg,wp,lp);
	}

	return result;
}



} /* namespace ComfortableWindows */
