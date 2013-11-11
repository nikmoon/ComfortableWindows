/*
 * test.cpp
 *
 *  Created on: 05 нояб. 2013 г.
 *      Author: karpachevnk
 */


#include <typeinfo>
#include "source/Controls/CButton.h"
#include "source/CDialogWindow.h"


using namespace ComfortableWindows;



class CMainWindow : public CDialogWindow
{
public:
	CMainWindow(HINSTANCE _hinst, LPCTSTR _title, SWindowRect &_rect);
	virtual ~CMainWindow();

	virtual LRESULT OnDestroy();
	virtual LRESULT OnCommandFromButton(CButton *pb, DWORD _ncode);

private:
	CButton *pButton, *pFixator;
	CCheckBox *pBox1;

};



CMainWindow::CMainWindow(HINSTANCE _hinst, LPCTSTR _title, SWindowRect &_rect)
	: CDialogWindow(TLWS_WINDOW_SIZIBLE_WITH_MINMAXBUTT, 0, _title, NULL, NULL, _hinst, _rect)
{
	SWindowRect buttRect = {10, 10, 100, 30};
	SWindowRect fixtRect = {150, 50, 100, 30};
	SWindowRect boxRect = {120, 10, 100, 30};

	pButton = new CButton(ECT_BUTTON,"Exit",101,_hinst,this,buttRect);
	pFixator = new CButton(ECT_FIXBUTTON,"Fix Op",102,_hinst,this,fixtRect);
	pBox1 = new CCheckBox(ECT_AUTOCHECKBOX, "Some check", 103, _hinst,this,boxRect);

	if (typeid(*pButton) == typeid(*pBox1))
		MessageBox(NULL, "Типы CButton и CCheckBox эквивалентны","Внимание",MB_OK);
	else
		MessageBox(NULL, "Типы CButton и CCheckBox НЕ эквивалентны","Внимание",MB_OK);

}


CMainWindow::~CMainWindow()
{
	delete pBox1;
	delete pFixator;
	delete pButton;
}

LRESULT
CMainWindow::OnDestroy()
{
	PostQuitMessage(0);
	return 0;
}


LRESULT
CMainWindow::OnCommandFromButton(CButton *_pb, DWORD _ncode)
{
	switch (_ncode)
	{
		case BN_CLICKED:
			if (_pb == pButton)
			{
				Destroy();
			}
			else if (_pb == pFixator)
			{
				MessageBox(GetHWnd(), "Вы нажали фиксирующуюся кнопку", "Внимание", MB_OK);
			}
			return 0;
		default:
			return 0;
	}
}



int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	SWindowRect winRect = {100, 100, 800, 600};
	CMainWindow *pWindow = new CMainWindow(hInst, "Standard Window", winRect);

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

