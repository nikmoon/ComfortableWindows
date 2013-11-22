/*
 * CBaseWindow.cpp
 *
 *  Created on: 05 нояб. 2013 г.
 *      Author: karpachevnk
 */

#include "CBaseWindow.h"

namespace ComfortableWindows
{


DWORD
CBaseWindow::sm_VisibleOnCreate = WS_VISIBLE;

//
//		Основной конструктор класса
//		-----------------------------------------------------
//
CBaseWindow::CBaseWindow(
	LPCTSTR _clname,		// имя оконного класса
	DWORD _style,			// основной стиль для окна
	DWORD _exstyle,			// расширенный стиль для окна
	LPCTSTR _title,			// заголовок окна
	CBaseWindow *_parent,	// родительское окно
	HMENU _hmenu,			// описатель меню окна
	HINSTANCE _hinst,		// описатель модуля, создающего окно
	const SWindowRect &_rect,	// геометрия окна
	LPVOID _pdata)			// дополнительные данные для создания окна
{
	// получим описатель родительского окна
	HWND hparent = (_parent == NULL) ? NULL : _parent->m_hWnd;

	// окно будет видимым, если хотя бы один из флагов установлен
	_style |= sm_VisibleOnCreate;

	// создадим окно
	m_hWnd = ::CreateWindowEx(_exstyle, _clname, _title, _style, _rect.x, _rect.y, _rect.cx, _rect.cy, hparent, _hmenu, _hinst, _pdata);
	// проверим на ошибки
	if (m_hWnd == NULL)
	{
		// здесь бросаем исключение
	}

	// инициализируем остальные поля экземпляра
	m_hInst = _hinst;
	m_ClassName = _clname;
	m_pParent = _parent;
	m_Movable = false;

	// выполняем связывание данного экземпляра с созданным системным окном
	Binding(m_hWnd);
}


//
//		Деструктор
//		----------------------------------
//
CBaseWindow::~CBaseWindow()
{
	// если на момент уничтожения экземпляра окно еще не уничтожено
	if (::IsWindow(m_hWnd))
	{
		// сигнализируем
		::MessageBox(NULL, "Экземпляр уничтожается, но окно существует", "Внимание", MB_OK);

		// генерируем исключение
	}
}


//
//		Дефолтный обработчик сообщений
//
//		Вызывается в случае отсутствия какого-либо обработчика
//		При необходимости может переопределяться
//
LRESULT
CBaseWindow::OnMessageDefault(UINT msg, WPARAM wp, LPARAM lp)
{
	return ::DefWindowProc(m_hWnd, msg, wp, lp);
};


//
//		Базовый обработчик сообщений
//
//		Переопределяемый для наследуемых классов
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
	// ищем элемент с указанным кодом уведомления
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
	// сначала попробуем найти элемент с указанным кодом уведомления
	for (SNotifyBindWithActionIndex &s : m_NtfyActionIndexArray)
	{
		if (s.m_NotifyCode == _ntfy)	// найден такой элемент
		{
			s.m_ActionIndex = _aindex;	// записываем индекс действия
			return;		// выход
		}
	}

	// элемент не найден, добавим
	m_NtfyActionIndexArray.push_back( {_ntfy,_aindex} );
}


DWORD
CBaseWindow::SetStyle(DWORD _style)
{
	DWORD oldStyle = ::SetWindowLongPtr(m_hWnd, GWL_STYLE, _style);
	::SetWindowPos(m_hWnd, 0, 0, 0, 0, 0, SWP_FRAMECHANGED|SWP_NOMOVE|SWP_NOSIZE|SWP_NOOWNERZORDER|SWP_NOZORDER);
	return oldStyle;
}


LRESULT CALLBACK
CBaseWindow::BaseWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	// получаем адрес связанного с окном экземпляра объекта
	CBaseWindow * pWindow = CBaseWindow::GetObjectPtr(hwnd);

	return (pWindow) ? pWindow->OnMessage(msg, wp, lp) : ::DefWindowProc(hwnd, msg, wp, lp);
}

LRESULT CALLBACK
CBaseWindow::MovableWindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	// получаем адрес связанного с окном экземпляра объекта
	CBaseWindow * pWindow = CBaseWindow::GetObjectPtr(hwnd);

	switch (msg)
	{
		case WM_NCHITTEST:
			if (::DefWindowProc(hwnd, msg, wp, lp) == HTCLIENT)
				return HTCAPTION;
			break;
		case WM_SIZE:
		case WM_MOVE:
			if (pWindow->GetParentWindow())
			{
				::InvalidateRect(pWindow->GetParentWindow()->GetHWnd(), NULL, TRUE);
			}
			::InvalidateRect(hwnd,NULL,TRUE);
			break;
		default:
			break;
	}

	return ::DefWindowProc(hwnd, msg, wp, lp);
}


void
CBaseWindow::InitMovable()
{
	// добавляем рамку, позволяющую изменять размер окна, сохраняя старый стиль окна
	m_PrevStyle = SetStyle(GetStyle() | WS_SIZEBOX);

	// разрешаем перемещение окна мышкой за любую его часть
	// для этого заменяем оконную процедуру, сохраняя старую
	m_PrevProc = InitSubclassing(m_hWnd, MovableWindowProc);
}


void
CBaseWindow::DoneMovable()
{
	// возвращаем прежний адрес оконной процедуры
	DoneSubclassing(m_hWnd, m_PrevProc);

	// возвращаем стиль окна
	SetStyle(m_PrevStyle);
}


void
CBaseWindow::ChangeMovable()
{
	if (m_Movable)
	{
		DoneMovable();
		m_Movable = false;
	}
	else
	{
		InitMovable();
		m_Movable = true;
	}
}


} /* namespace ComfortableWindows */
