/*
 * test.cpp
 *
 *  Created on: 05 ����. 2013 �.
 *      Author: karpachevnk
 */


#include "source/Controls/CButton.h"
#include "source/Controls/CEditBox.h"
#include "source/CDialogWindow.h"
#include "source/CBaseMenu.h"
#include <string>


using namespace std;
using namespace ComfortableWindows;


enum EActionIndex : int
{
	EAI_CLOSEAPP = 0,
	EAI_SHOWMESSAGE,
	EAI_ADDMENUITEM
};


class CMainWindow : public CDialogWindow
{
public:
	CMainWindow(HINSTANCE _hinst, LPCTSTR _title, const SWindowRect &_rect);
	virtual ~CMainWindow();

	virtual LRESULT OnMessage(UINT msg, WPARAM wp, LPARAM lp);

//	virtual LRESULT OnCommand(UINT msg, WPARAM wp, LPARAM lp);
	virtual LRESULT OnPaint(UINT msg, WPARAM wp, LPARAM lp);
	virtual LRESULT OnDestroy(UINT msg, WPARAM wp, LPARAM lp);
	virtual LRESULT ExecuteAction(int _aindex, UINT _msg, WPARAM wp, LPARAM lp);

private:
	CGroupBox *pGroupBox;
	CEditBox *pEditBox;
	CButton *pButtonExit;

	CMenuBar *pMenuBar;
	CContextMenu *pMenu, *pSubMenu;
};



CMainWindow::CMainWindow(HINSTANCE _hinst, LPCTSTR _title, const SWindowRect &_rect)
	: CDialogWindow(EDWS_WINDOW_SIZIBLE_WITH_MINMAXBUTT, 0, _title, NULL, NULL, _hinst, _rect)
{
	pMenuBar = new CMenuBar(*this);	//������� ������� ���� ����
	pMenu = new CContextMenu();		// ������� ����������� ����
	pSubMenu = new CContextMenu();	// ��������� �������

	// �������������� ��������� �������
	pSubMenu->AddItemAtEnd("������� ����� �����", EAI_ADDMENUITEM);
	pSubMenu->AddItemAtEnd("�����", EAI_CLOSEAPP);

	// ��������� �������� ���� ����
	pMenuBar->AddItemAtEnd("�������", *pSubMenu);
	pMenuBar->Update();

	// ��������� ����������� ����
	pMenu->AddItemAtEnd("�������", *pSubMenu);
//	pMenu->AddItemAtEnd("����� ��������", EAI_SHOWMESSAGE);
//	pMenu->AddItemAtEnd("�����",EAI_CLOSEAPP);

	// ������� �������� ����������
	pGroupBox = new CGroupBox("��������� ��������", 99, _hinst, this, {10,10,200,130} );
	pEditBox = new CEditBox(ECT_EDITBOX_MULTILINE_ALLSCROLL,"123",this,100,_hinst,{20,30,100,65});
	pButtonExit = new CButton(ECT_BUTTON,"�����",101,_hinst,this,{ 30, 105, 100, 30});
	pButtonExit->OnClick(EAI_CLOSEAPP);
}


CMainWindow::~CMainWindow()
{
	delete pButtonExit;
	delete pEditBox;
	delete pGroupBox;
	delete pSubMenu;
	delete pMenu;
	delete pMenuBar;
}



LRESULT
CMainWindow::OnMessage(UINT msg, WPARAM wp, LPARAM lp)
{
	LRESULT result;

	switch (msg)
	{
		case WM_CONTEXTMENU:
			LRESULT hitarea;
			hitarea = OnMessage(WM_NCHITTEST, 0, lp);
			if (hitarea == HTCLIENT)
			{
				//MessageBox(m_hWnd,"����� �� ������ ���� ����","123",MB_OK);
				WORD x,y;
				x = GET_X_LPARAM(lp);
				y = GET_Y_LPARAM(lp);
				pMenu->Display(x,y,*this);
				result = 0;
			}
			else
			{
				result = CDialogWindow::OnMessage(msg,wp,lp);
			}
			break;
		default:
			result = CDialogWindow::OnMessage(msg,wp,lp);
			break;
	}

	return result;
}

/*
LRESULT
CMainWindow::OnCommand(UINT msg, WPARAM wp, LPARAM lp)
{
	LRESULT result;

	result = CDialogWindow::OnCommand(msg,wp,lp);

	return result;

}
*/

LRESULT
CMainWindow::OnPaint(UINT msg, WPARAM wp, LPARAM lp)
{
	HDC hDC;
	PAINTSTRUCT ps;

	hDC = ::BeginPaint(GetHWnd(), &ps);
	::TextOut(hDC, 20, 150, "������������ WM_PAINT", 15);
	::EndPaint(GetHWnd(), &ps);

	return 0;
}


LRESULT
CMainWindow::OnDestroy(UINT msg, WPARAM wp, LPARAM lp)
{
//	::DestroyMenu(m_hMenu);
	PostQuitMessage(0);
	return 0;
}


LRESULT
CMainWindow::ExecuteAction(int _aindex, UINT _msg,  WPARAM wp, LPARAM lp)
{
	LRESULT result = 0;

	switch (_aindex)
	{
		case EAI_CLOSEAPP:	// ������ �� ������ pButton
			Destroy();
			break;
		case EAI_SHOWMESSAGE:
			MessageBox(m_hWnd, "�� ������� ��������!!! )))", "���-�� ���", MB_OK);
			break;
		case EAI_ADDMENUITEM:
			pSubMenu->AddItemAtStart("������� �����", EAI_ADDMENUITEM);
			break;
		default:
			result = CDialogWindow::ExecuteAction(_aindex,_msg,wp,lp);
			break;
	}
	return result;
}



int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	CMainWindow *pWindow = new CMainWindow(hInst, "Standard Window", {200, 200, 800, 600});

	pWindow->Show();
	pWindow->UpdateContent();

	BOOL bRet;
	MSG msg;

	while((bRet = ::GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		if (bRet == -1)
		{	// ����� ������� �� ������
			break;
		}
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
	}

	delete pWindow;
	return msg.lParam;
}

