/*
 * CBaseWindow.cpp
 *
 *  Created on: 05 но€б. 2013 г.
 *      Author: karpachevnk
 */

#include "CBaseWindow.h"

namespace ComfortableWindows
{


DWORD
CBaseWindow::sm_VisibleOnCreate = WS_VISIBLE;

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

	// окно будет видимым, если хот€ бы один из флагов установлен
	_style |= sm_VisibleOnCreate;

	// создадим окно
	m_hWnd = ::CreateWindowEx(_exstyle, _clname, _title, _style, _rect.x, _rect.y, _rect.cx, _rect.cy, hparent, _hmenu, _hinst, _pdata);
	// проверим на ошибки
	if (m_hWnd == NULL)
	{
		// здесь бросаем исключение
	}

	// инициализируем остальные пол€ экземпл€ра
	m_hInst = _hinst;
	m_ClassName = _clname;
	m_pParent = _parent;

	// выполн€ем св€зывание данного экземпл€ра с созданным системным окном
	Binding(m_hWnd);
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
	LRESULT result;

	switch (msg)
	{
		case WM_PAINT:
			result = OnPaint(msg,wp,lp);
			break;
		case WM_DESTROY:
			result = OnDestroy(msg,wp,lp);
			break;
		case WM_COMMAND:
			result = OnCommand(msg,wp,lp);
			break;
		default:
			result = OnMessageDefault(msg,wp,lp);
			break;
	}
	return result;
}


LRESULT
CBaseWindow::OnPaint(UINT msg, WPARAM wp, LPARAM lp)
{
	return OnMessageDefault(msg,wp,lp);
}


LRESULT
CBaseWindow::OnDestroy(UINT msg, WPARAM wp, LPARAM lp)
{
	return OnMessageDefault(msg,wp,lp);
}


LRESULT
CBaseWindow::OnCommand(UINT msg, WPARAM wp, LPARAM lp)
{
	return OnMessageDefault(msg,wp,lp);
}


LRESULT
CBaseWindow::ExecuteAction(int _aindex, UINT _msg, WPARAM _wp, LPARAM _lp)
{
	return OnMessageDefault(_msg,_wp,_lp);
}



int
CBaseWindow::GetActionIndex(WORD _ntfy)
{
	// ищем элемент с указанным кодом уведомлени€
	for (SNotifyBindWithActionIndex &s : m_NtfyActionIndexArray)
	{
		if (s.m_NotifyCode == _ntfy)	// найден такой элемент
			return s.m_ActionIndex;
	}

	// элемент не найден
	return -1;
}

void
CBaseWindow::SetActionIndex(WORD _ntfy, int _aindex)
{
	// сначала попробуем найти элемент с указанным кодом уведомлени€
	for (SNotifyBindWithActionIndex &s : m_NtfyActionIndexArray)
	{
		if (s.m_NotifyCode == _ntfy)	// найден такой элемент
		{
			s.m_ActionIndex = _aindex;	// записываем индекс действи€
			return;		// выход
		}
	}

	// элемент не найден, добавим
	m_NtfyActionIndexArray.push_back( {_ntfy,_aindex} );
}


LRESULT CALLBACK
CBaseWindow::BaseWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	// получаем адрес св€занного с окном экземпл€ра объекта
	CBaseWindow * pWindow = CBaseWindow::GetObjectPtr(hwnd);

	return (pWindow) ? pWindow->OnMessage(msg, wp, lp) : ::DefWindowProc(hwnd, msg, wp, lp);
}


} /* namespace ComfortableWindows */
