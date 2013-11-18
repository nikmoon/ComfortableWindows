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
#include "source/CBaseMenu.h"
#include <string>


using namespace std;
using namespace ComfortableWindows;


enum EActionIndex : int
{
	EAI_CLOSEAPP = 0,
	EAI_SHOWMESSAGE
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
	CContextMenu *pMenu;
};



CMainWindow::CMainWindow(HINSTANCE _hinst, LPCTSTR _title, const SWindowRect &_rect)
	: CDialogWindow(EDWS_WINDOW_SIZIBLE_WITH_MINMAXBUTT, 0, _title, NULL, NULL, _hinst, _rect)
{
	pMenuBar = new CMenuBar(*this);
	pMenu = new CContextMenu();

	CSubMenu subMenu = CSubMenu();


	pMenuBar->AddItem("Выход1",EAI_CLOSEAPP);
	pMenuBar->AddItem("Выход2",EAI_CLOSEAPP);
	pMenuBar->AddItem("Выход3",EAI_CLOSEAPP);

	pMenu->AddItem("Подменю", &subMenu);
	pMenu->AddItem("Некое действие", EAI_SHOWMESSAGE);
	pMenu->AddItem("Выход",EAI_CLOSEAPP);

	subMenu.AddItem("Опять выход", EAI_CLOSEAPP);
	subMenu.AddItem("Тут тоже выход", EAI_CLOSEAPP);

	pMenuBar->AddItem("Выход4",&subMenu);
	pMenuBar->Update();

	pGroupBox = new CGroupBox("Маленький редактор", 99, _hinst, this, {10,10,200,130} );
	pEditBox = new CEditBox(ECT_EDITBOX_MULTILINE_ALLSCROLL,"123",this,100,_hinst,{20,30,100,65});
	pButtonExit = new CButton(ECT_BUTTON,"Выход",101,_hinst,this,{ 30, 105, 100, 30});
	pButtonExit->OnClick(EAI_CLOSEAPP);
}


CMainWindow::~CMainWindow()
{
	delete pButtonExit;
	delete pEditBox;
	delete pGroupBox;
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
				//MessageBox(m_hWnd,"Вроде бы должно быть меню","123",MB_OK);
				WORD x,y;
				x = GET_X_LPARAM(lp);
				y = GET_Y_LPARAM(lp);
				pMenu->Display(x,y,*this);
			}
			result = 0;
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
	::TextOut(hDC, 20, 150, "Обрабатываем WM_PAINT", 15);
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
		case EAI_CLOSEAPP:	// щелчок по кнопке pButton
			Destroy();
			break;
		case EAI_SHOWMESSAGE:
			MessageBox(m_hWnd, "Вы выбрали действие!!! )))", "Как-то так", MB_OK);
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

