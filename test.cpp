/*
 * test.cpp
 *
 *  Created on: 05 но€б. 2013 г.
 *      Author: karpachevnk
 */


#include "source/CBaseWindow.h"
#include "source/COwnerWindow.h"
#include "source/Controls/CButton.h"


using namespace ComfortableWindows;



class CMainWindow : public COwnerWindow
{
public:
	CMainWindow(HINSTANCE _hinst, LPCTSTR _title, SWindowRect &_rect);

	virtual LRESULT OnDestroy();

private:

};



CMainWindow::CMainWindow(HINSTANCE _hinst, LPCTSTR _title, SWindowRect &_rect)
	: COwnerWindow(TLWS_WINDOW_SIZIBLE_WITH_MINMAXBUTT, 0, _title, NULL, NULL, _hinst, _rect)
{

}


LRESULT
CMainWindow::OnDestroy()
{
	PostQuitMessage(0);
	return 0;
}




int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	SWindowRect winRect = {100, 100, 800, 600};
	SWindowRect buttRect = {10, 10, 100, 30};
	SWindowRect fixtRect = {150, 50, 100, 30};
	CMainWindow *pWindow = new CMainWindow(hInst, "Standard Window", winRect);

	CChildWindow *pButton = new CButton("Exit",101,hInst,pWindow,buttRect);
	CChildWindow *pFixator = new CFixButton("Fix Op",102,hInst,pWindow,fixtRect);

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

	delete pFixator;
	delete pButton;
	delete pWindow;
	return msg.lParam;
}

