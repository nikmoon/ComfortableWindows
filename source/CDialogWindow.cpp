/*
 * CDialogWindow.cpp
 *
 *  Created on: 11 нояб. 2013 г.
 *      Author: karpachevnk
 */

#include "CDialogWindow.h"


namespace ComfortableWindows
{

// текущее общее число созданных диалоговых окон
int
CDialogWindow::sm_DlgWndCount = 0;


LPCTSTR
CDialogWindow::GetDlgWndClsName(HINSTANCE _hinst)
{
	static LPCTSTR clname = "CDlgWndCls";

	// проверим, зарегистрирован ли класс диалогового окна
	if (sm_DlgWndCount == 0)	// не зарегистрирован
	{
		// регистрируем класс диалогового окна
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

		// пытаемся зарегистрировать оконный класс
		if (::RegisterClassEx(&wc) == 0)
		{	// тута генерируем исключение
			throw(1);
		}

	}

	++sm_DlgWndCount;	// увеличиваем счетчик диалоговых окон
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
	// уменьшаем счетчик диалоговых окон
	--sm_DlgWndCount;

	// если это было последнее диалоговое окно
	if (sm_DlgWndCount == 0)
	{
		// отменяем регистрацию класса диалогового окна
		::UnregisterClass(m_ClassName.c_str(),m_hInst);
	}
}


LRESULT
CDialogWindow::OnCommand(UINT msg, WPARAM wp, LPARAM lp)
{
	LRESULT result;

	//
	// проверяем уведомление от элемента управления
	// ---------------------------------------------------------
	//
	if (lp != 0)	// получено уведомление от дочернего элемента
	{
		CBaseWindow *pCtrl = CBaseWindow::GetObjectPtr((HWND)lp);	// получаем дочерний элемент
		if (pCtrl)
		{
			int aindex = pCtrl->GetActionIndex(HIWORD(wp));		// получаем от дочернего элемента сохраненный индекс действия
			result = ExecuteAction(aindex,msg,wp,lp);	// выполняем требуемое действие
		}
		else
		{
			result = OnMessageDefault(msg,wp,lp);
		}
	}
	//
	// проверяем уведомление от меню
	// ---------------------------------------------------------
	//
	else if (HIWORD(wp) == 0)
	{
		result = ExecuteAction(LOWORD(wp),msg,wp,lp);	// выполняем требуемое действие из меню
	}
	else
	{
		result = OnMessageDefault(msg,wp,lp);
	}

	return result;
}



} /* namespace ComfortableWindows */
