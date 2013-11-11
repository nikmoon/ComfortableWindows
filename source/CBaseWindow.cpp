/*
 * CBaseWindow.cpp
 *
 *  Created on: 05 но€б. 2013 г.
 *      Author: karpachevnk
 */

#include "CBaseWindow.h"

namespace ComfortableWindows
{



CBaseWindow::CBaseWindow(
	LPCTSTR _clname,
	DWORD _style,
	DWORD _exstyle,
	LPCTSTR _title,
	CBaseWindow *_parent,
	HMENU _hmenu,
	HINSTANCE _hinst,
	SWindowRect &_rect,
	LPVOID _pdata)
{
	// получим описатель родительского окна
	HWND hparent = (_parent == NULL) ? NULL : _parent->m_hWnd;

	// создадим окно
	m_hWnd = ::CreateWindowEx(_exstyle, _clname, _title, _style, _rect.x, _rect.y, _rect.cx, _rect.cy, hparent, _hmenu, _hinst, _pdata);
	// проверим на ошибки
	if (m_hWnd == NULL)
	{
		// здесь бросаем исключение
	}

	// выполн€ем св€зывание
	SetWndPtr(m_hWnd, this);

	// инициализируем остальные пол€ экземпл€ра
	m_hInst = _hinst;
	m_ClassName = _clname;
	m_pParent = _parent;
}





CBaseWindow::~CBaseWindow()
{
	// если на момент уничтожени€ экземпл€ра окно еще не уничтожено
	if (::IsWindow(m_hWnd))
	{
		// сигнализируем
		::MessageBox(NULL, "Ёкземпл€р уничтожаетс€, но окно существует", "¬нимание", MB_OK);

		// генерируем исключение
	}
}


LRESULT
CBaseWindow::OnMessage(UINT msg, WPARAM wp, LPARAM lp)
{
	LRESULT result;

	switch(msg)
	{
		case WM_CLOSE:
			result = OnClose();
			break;
		case WM_DESTROY:
			result = OnDestroy();
			break;
		default:
			result = OnMessageDefault(msg, wp, lp);
	}

	return result;
}


CBaseWindow *
CBaseWindow::GetWndPtr(HWND hwnd)
{
	return (CBaseWindow*)::GetWindowLongPtr(hwnd, GWLP_USERDATA);
}




WNDPROC
CBaseWindow::GetWndProc(HWND hwnd)
{
	return (WNDPROC)::GetWindowLongPtr(hwnd, GWLP_WNDPROC);
}



LRESULT CALLBACK
CBaseWindow::BaseWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	// получаем адрес св€занного с окном экземпл€ра объекта
	CBaseWindow * pWindow = CBaseWindow::GetWndPtr(hwnd);

	LRESULT result;

	if (pWindow == NULL)
	{
		result = ::DefWindowProc(hwnd, msg, wp, lp);
	}
	else
	{
		result = pWindow->OnMessage(msg, wp, lp);
	}

	return result;
}


void
CBaseWindow::SetWndPtr(HWND _hwnd, CBaseWindow *_obj)
{
	::SetWindowLongPtr(_hwnd, GWLP_USERDATA, (LONG_PTR)_obj);
}


WNDPROC
CBaseWindow::SetWndProc(HWND _hwnd, WNDPROC _proc)
{
	return (WNDPROC)::SetWindowLongPtr(_hwnd, GWLP_WNDPROC, (LONG_PTR)_proc);
}


} /* namespace ComfortableWindows */
