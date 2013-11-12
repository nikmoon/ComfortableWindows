/*
 * CBaseWindow.cpp
 *
 *  Created on: 05 но€б. 2013 г.
 *      Author: karpachevnk
 */

#include "CBaseWindow.h"

namespace ComfortableWindows
{


//
//		ќсновной конструктор класса
//		-----------------------------------------------------
//
CBaseWindow::CBaseWindow(
	LPCTSTR _clname,		// им€ оконного класса
	DWORD _style,			// основной стиль дл€ окна
	DWORD _exstyle,			// расширенный стиль дл€ окна
	LPCTSTR _title,			// заголовок окна
	CBaseWindow *_parent,	// родительское окно
	HMENU _hmenu,			// описатель меню окна
	HINSTANCE _hinst,		// описатель модул€, создающего окно
	const SWindowRect &_rect,	// геометри€ окна
	LPVOID _pdata)			// дополнительные данные дл€ создани€ окна
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

	// выполн€ем св€зывание данного экземпл€ра с созданным системным окном
	Binding(m_hWnd, this);

	// инициализируем остальные пол€ экземпл€ра
	m_hInst = _hinst;
	m_ClassName = _clname;
	m_pParent = _parent;
}


//
//		ƒеструктор
//		----------------------------------
//
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


//
//		ƒефолтный обработчик сообщений
//
//		¬ызываетс€ в случае отсутстви€ какого-либо обработчика
//		ѕри необходимости может переопредел€тьс€
//
LRESULT
CBaseWindow::OnMessageDefault(UINT msg, WPARAM wp, LPARAM lp)
{
	return ::DefWindowProc(m_hWnd, msg, wp, lp);
};


//
//		Ѕазовый обработчик сообщений
//
//		ѕереопредел€емый дл€ наследуемых классов
//
LRESULT
CBaseWindow::OnMessage(UINT msg, WPARAM wp, LPARAM lp)
{
	return OnMessageDefault(msg, wp, lp);
}


LRESULT CALLBACK
CBaseWindow::BaseWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	// получаем адрес св€занного с окном экземпл€ра объекта
	CBaseWindow * pWindow = CBaseWindow::GetObjectPtr(hwnd);

	return (pWindow) ? pWindow->OnMessage(msg, wp, lp) : ::DefWindowProc(hwnd, msg, wp, lp);
}


} /* namespace ComfortableWindows */
