/*
 * COwnerWindow.cpp
 *
 *  Created on: 06 нояб. 2013 г.
 *      Author: karpachevnk
 */

#include "COwnerWindow.h"
#include "CChildWindow.h"

namespace ComfortableWindows
{

// дефолтный стиль дефолтного оконного класса
UINT
COwnerWindow::m_StdWndClassStyle = CS_HREDRAW|CS_VREDRAW;

// дефолтный класс для стандартных окон
WNDCLASSEX *
COwnerWindow::m_StdWndClass = NULL;

// количество созданных окон дефолтного класса
int
COwnerWindow::m_StdWndCount = 0;


//
//		Условная регистрация дефолтного оконного класса
//		----------------------------------------------------------
//
//		Дефолтный класс регистрируется, если не зарегистрирован.
//		Возвращается имя оконного класса.
//
LPCTSTR
COwnerWindow::RegisterStdWndClass(HINSTANCE _hinst)
{
	// если стандартный класс еще не зарегистрирован, регистрируем
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

		// пытаемся зарегистрировать оконный класс
		if (::RegisterClassEx(m_StdWndClass) == 0)
		{	// тута генерируем исключение
			throw(1);
		}
	}

	return m_StdWndClass->lpszClassName;
}


//
//		Отмена регистрации дефолтного оконного класса
//		--------------------------------------------------------------
//
//		Если окон дефолтного класса больше нет, производится отмена регистрации дефолтного оконного класса
//
void
COwnerWindow::UnregisterStdWndClass()
{
	{	// отменяем системную регистрацию класса
		if (::UnregisterClass(m_StdWndClass->lpszClassName, m_StdWndClass->hInstance) == 0)
		{	// какая-то ошибка, генерируем исключение
			throw(1);
		}

		delete m_StdWndClass;	// удаляем структуру из памяти
		m_StdWndClass = NULL;	// обнуляем указатель
	}
}




COwnerWindow::COwnerWindow(LPCTSTR _clname, ETopLevelWindowStyle _style, DWORD _exstyle, LPCTSTR _title, CBaseWindow *_parent, HMENU _hmenu,
	HINSTANCE _hinst, const SWindowRect &_rect, LPVOID _pdata)
	: CBaseWindow(_clname, _style, _exstyle, _title, _parent, _hmenu, _hinst, _rect, _pdata)
{
	// окно создано на основе пользовательского оконного класса
	m_IsStdWndClass = false;
}



COwnerWindow::COwnerWindow(ETopLevelWindowStyle _style, DWORD _exstyle, LPCTSTR _title, CBaseWindow *_parent, HMENU _hmenu,
	HINSTANCE _hinst, const SWindowRect &_rect, LPVOID _pdata)
	: CBaseWindow(RegisterStdWndClass(_hinst), _style, _exstyle, _title, _parent, _hmenu, _hinst, _rect, _pdata)
{
	// окно создано на основе стандартного оконного класса
	m_IsStdWndClass = true;

	// инкрементируем счетчик окон стандартного класса
	m_StdWndCount++;
}


COwnerWindow::~COwnerWindow()
{
	// декрементируем счетчик окон стандартного класса
	m_StdWndCount--;

	// если было окно дефолтного класса и оно было последним
	if ((m_IsStdWndClass) && (m_StdWndCount == 0))
	{	// отменяем регистрацию дефолтного класса
		UnregisterStdWndClass();
	}
}

LRESULT
COwnerWindow::OnMessage(UINT msg, WPARAM wp, LPARAM lp)
{
	LRESULT result;

	switch (msg)
	{
		case WM_COMMAND:
			if (lp != 0)	// если не нуль, значит уведомление от элемента управления
			{
				CChildWindow *pwin = (CChildWindow*)(GetObjectPtr((HWND)lp));
				int aindex = pwin->aIndex(HIWORD(wp));
				result = ExecuteAction(aindex, WM_COMMAND, wp, lp);
			}
			else
			{
				result = CBaseWindow::OnMessage(msg,wp,lp);
			}
			break;
		default:
			result = CBaseWindow::OnMessage(msg,wp,lp);
			break;
	}
	return result;
}

LRESULT
COwnerWindow::ExecuteAction(int _aindex, UINT _msg,  WPARAM wp, LPARAM lp)
{
	return CBaseWindow::OnMessage(_msg, wp, lp);
}

} /* namespace ComfortableWindows */
