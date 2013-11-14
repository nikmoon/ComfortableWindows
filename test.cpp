/*
 * test.cpp
 *
 *  Created on: 05 но€б. 2013 г.
 *      Author: karpachevnk
 */


#include <typeinfo>
#include "source/Controls/CButton.h"
#include "source/CDialogWindow.h"


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

	virtual LRESULT OnPaint(UINT msg, WPARAM wp, LPARAM lp);
	virtual LRESULT OnDestroy(UINT msg, WPARAM wp, LPARAM lp);
	virtual LRESULT ExecuteAction(int _aindex, UINT _msg, WPARAM wp, LPARAM lp);

private:
	CButton *pButton, *pFixator;
	CCheckBox *pBox1;
};



CMainWindow::CMainWindow(HINSTANCE _hinst, LPCTSTR _title, const SWindowRect &_rect)
	: CDialogWindow(EDWS_WINDOW_SIZIBLE_WITH_MINMAXBUTT, 0, _title, NULL, NULL, _hinst, _rect)
{
	(pButton = new CButton(ECT_BUTTON,"Exit",101,_hinst,this,{10, 10, 100, 30}))->OnClick(EAI_CLOSEAPP);
	(pFixator = new CButton(ECT_BUTTON_FIXABLE,"Fix Op",102,_hinst,this,{150, 50, 100, 30}))->OnClick(EAI_CLOSEAPP);
	(pBox1 = new CCheckBox(ECT_CHECKBOX_AUTO, "Exit on Button", 103, _hinst,this,{120, 10, 130, 30}))->OnClick(EAI_CLOSEAPP);
}


CMainWindow::~CMainWindow()
{
	delete pBox1;
	delete pFixator;
	delete pButton;
}

LRESULT
CMainWindow::OnMessage(UINT msg, WPARAM wp, LPARAM lp)
{
	LRESULT result;

	switch (msg)
	{
		default:
			result = CDialogWindow::OnMessage(msg,wp,lp);
			break;
	}

	return result;
}


LRESULT
CMainWindow::OnPaint(UINT msg, WPARAM wp, LPARAM lp)
{
	HDC hDC;
	PAINTSTRUCT ps;

	hDC = ::BeginPaint(GetHWnd(), &ps);
	::TextOut(hDC, 20, 150, "ќбрабатываем WM_PAINT", 15);
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

