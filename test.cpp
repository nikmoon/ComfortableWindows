/*
 * test.cpp
 *
 *  Created on: 05 нояб. 2013 г.
 *      Author: karpachevnk
 */


#include <typeinfo>
#include "source/Controls/CButton.h"
#include "source/Controls/CEditBox.h"
#include "source/CDialogWindow.h"
#include <string>


using namespace std;
using namespace ComfortableWindows;


enum EActionIndex : int
{
	EAI_CLOSEAPP = 0,
};


class CMainWindow : public CDialogWindow
{
public:
	CMainWindow(HINSTANCE _hinst, LPCTSTR _title, const SWindowRect &_rect);
	virtual ~CMainWindow();

	virtual LRESULT OnMessage(UINT msg, WPARAM wp, LPARAM lp);

	virtual LRESULT OnCommand(UINT msg, WPARAM wp, LPARAM lp);
	virtual LRESULT OnPaint(UINT msg, WPARAM wp, LPARAM lp);
	virtual LRESULT OnDestroy(UINT msg, WPARAM wp, LPARAM lp);
	virtual LRESULT ExecuteAction(int _aindex, UINT _msg, WPARAM wp, LPARAM lp);

private:
	CGroupBox *pGroupBox;
	CEditBox *pEditBox;
	CButton *pButtonExit;
};



CMainWindow::CMainWindow(HINSTANCE _hinst, LPCTSTR _title, const SWindowRect &_rect)
	: CDialogWindow(EDWS_WINDOW_SIZIBLE_WITH_MINMAXBUTT, 0, _title, NULL, NULL, _hinst, _rect)
{
	MENUITEMINFO mii;
	string menuName = "Выход";

	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_TYPE | MIIM_ID;
	mii.fType = MFT_STRING;
	mii.dwTypeData = const_cast<LPTSTR>(menuName.c_str());
	mii.cch = menuName.length();
	mii.wID = 10;

	HMENU hMenu = ::CreateMenu();
	::InsertMenuItemA(hMenu, 0, TRUE, &mii);

	::SetMenu(m_hWnd,hMenu);

	pGroupBox = new CGroupBox("Маленький редактор", 99, _hinst, this, {10,10,200,130} );
	pEditBox = new CEditBox(ECT_EDITBOX_MULTILINE_ALLSCROLL,"123",this,100,_hinst,{20,30,100,65});
	pButtonExit = new CButton(ECT_BUTTON,"Выход",101,_hinst,this,{ 30, 105, 100, 30});
	pButtonExit->OnClick(EAI_CLOSEAPP);
}


CMainWindow::~CMainWindow()
{
	delete pEditBox;
	delete pGroupBox;
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
				MessageBox(m_hWnd,"Вроде бы должно быть меню","123",MB_OK);
			result = CDialogWindow::OnMessage(msg,wp,lp);
			break;
		default:
			result = CDialogWindow::OnMessage(msg,wp,lp);
			break;
	}

	return result;
}


LRESULT
CMainWindow::OnCommand(UINT msg, WPARAM wp, LPARAM lp)
{
	LRESULT result;

	if ((lp == 0) && (HIWORD(wp) == 0))	// получено уведомление от меню
	{
		switch (LOWORD(wp))
		{
			case 10:
				result = ExecuteAction(EAI_CLOSEAPP,msg,wp,lp);
				break;
			default:
				result = CDialogWindow::OnCommand(msg,wp,lp);
				break;
		}
	}
	else
	{
		result = CDialogWindow::OnCommand(msg,wp,lp);
	}

	return result;

}


LRESULT
CMainWindow::OnPaint(UINT msg, WPARAM wp, LPARAM lp)
{
	HDC hDC;
	PAINTSTRUCT ps;

	hDC = ::BeginPaint(GetHWnd(), &ps);
	::TextOut(hDC, 20, 150, "Обрабатываем WM_PAINT", 15);
	::EndPaint(GetHWnd(), &ps);

	return 0;
}


LRESULT
CMainWindow::OnDestroy(UINT msg, WPARAM wp, LPARAM lp)
{
	PostQuitMessage(0);
	return 0;
}


LRESULT
CMainWindow::ExecuteAction(int _aindex, UINT _msg,  WPARAM wp, LPARAM lp)
{
	LRESULT result = 0;

	switch (_aindex)
	{
		case EAI_CLOSEAPP:	// щелчок по кнопке pButton
			Destroy();
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
		{	// здесь выходим по ошибке
			break;
		}
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
	}

	delete pWindow;
	return msg.lParam;
}

