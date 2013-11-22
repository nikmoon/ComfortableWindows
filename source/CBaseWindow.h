/*
 * CBaseWindow.h
 *
 *  Created on: 05 нояб. 2013 г.
 *      Author: karpachevnk
 */

#ifndef CBASEWINDOW_H_
#define CBASEWINDOW_H_

#include <windows.h>
#include <string>
#include <vector>


#undef GetClassName		// данный идентификатор будет применяться в качестве имени метода

using namespace std;


namespace ComfortableWindows
{

//
//	Координаты и размеры системного окна
//
struct SWindowRect
{
	int x, y, cx, cy;
};


//
//	Структура связи индекса действия родительского окна m_ActionIndex, которое
//	должно выполняться при получении им уведомления m_NotifyCode от дочернего окна
//
//	Любое дочернее окно, которое может посылать родительскому окну уведомления,
//	должно содержать соответствующее количеству уведомлений число таких структур.
//	Индексы действий  могут передаваться родительским окном дочернему различными способами.
//
//	Описание принципа действия:
//		Пусть дочернее окно может послать родит. окну 2 уведомления MSG_CREATED и MSG_DESTROYED.
//	Значит доч. окно должно содержать не меньше 2 таких структур. После создания или в процессе
//	создания (через конструктор) род. окно сообщает доч. окну какой индекс действия должен быть
//	связан с соответствующим уведомление.
//		Когда род. окно получает уведомление от дочернего, оно дополнительно запрашивает
//	у дочернего, какой индекс действия связан с данным уведомление, и на основе этого индекса
//	понимает, какие действия нужно предпринять.
//	Получилась несложная система обработки уведомлений от дочерних окон.
//
struct SNotifyBindWithActionIndex
{
	WORD m_NotifyCode;	// код уведомления
	int m_ActionIndex;	// индекс действия
};


//
//	Базовый класс оконной библиотеки
//
class CBaseWindow
{
public:
	CBaseWindow(LPCTSTR _clname, DWORD _style, DWORD _exstyle, LPCTSTR _title, CBaseWindow *_parent, HMENU _hmenu,
		HINSTANCE _hinst, const SWindowRect &_rect, LPVOID _pdata = NULL);

	virtual ~CBaseWindow();

	// ФЛАГИ
	static void ShowOnCreate(bool _show = true) { if (_show) sm_VisibleOnCreate = WS_VISIBLE; else sm_VisibleOnCreate = 0; };

	// ГЕТТЕРЫ
	static CBaseWindow *GetObjectPtr(HWND _hwnd) { return (CBaseWindow*)::GetWindowLongPtr(_hwnd, GWLP_USERDATA); };
	static WNDPROC GetWndProc(HWND _hwnd) { return (WNDPROC)::GetWindowLongPtr(_hwnd, GWLP_WNDPROC); };

	HWND GetHWnd() const					{ return m_hWnd; };
	HINSTANCE GetHInst() const				{ return m_hInst; };
	LPCTSTR GetClassName() const			{ return m_ClassName.c_str(); };
	CBaseWindow *GetParentWindow() const	{ return m_pParent; };
	DWORD GetStyle() const					{ return ::GetWindowLongPtr(m_hWnd, GWL_STYLE); };

	// МЕТОДЫ
	void Show() 			{ ::ShowWindow(m_hWnd, SW_SHOW); };
	void Hide() 			{ ::ShowWindow(m_hWnd, SW_HIDE); };
	void UpdateContent() 	{ ::UpdateWindow(m_hWnd); };
	void Destroy() 			{ ::DestroyWindow(m_hWnd); };
	DWORD SetStyle(DWORD _style);

	int GetActionIndex(WORD _ntfy);

	static WNDPROC InitSubclassing(HWND _hwnd, WNDPROC _proc) { return (WNDPROC)::SetWindowLongPtr(_hwnd, GWLP_WNDPROC, (LONG_PTR)_proc); };
	static WNDPROC DoneSubclassing(HWND _hwnd, WNDPROC _baseproc) { return InitSubclassing(_hwnd, _baseproc); };

	void InitMovable();
	void DoneMovable();
	void ChangeMovable();

protected:
	HINSTANCE m_hInst;
	HWND m_hWnd;
	string m_ClassName;
	CBaseWindow *m_pParent;

	DWORD m_PrevStyle;
	WNDPROC m_PrevProc;

	void SetActionIndex(WORD _ntfy, int _aindex);

	static LRESULT CALLBACK BaseWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
	static LRESULT CALLBACK MovableWindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
	virtual LRESULT OnMessageDefault(UINT msg, WPARAM wp, LPARAM lp);
	virtual LRESULT OnMessage(UINT msg, WPARAM wp, LPARAM lp);
	virtual LRESULT OnPaint(UINT msg, WPARAM wp, LPARAM lp);
	virtual LRESULT OnDestroy(UINT msg, WPARAM wp, LPARAM lp);
	virtual LRESULT OnCommand(UINT msg, WPARAM wp, LPARAM lp);

	virtual LRESULT ExecuteAction(int _aindex, UINT _msg, WPARAM _wp, LPARAM _lp);

private:
	void Binding(HWND _hwnd) { ::SetWindowLongPtr(_hwnd, GWLP_USERDATA, (LONG_PTR)this); };

	static DWORD sm_VisibleOnCreate;
	bool m_Movable;

	// массив структур связи уведомлений и индексов действия;
	vector<SNotifyBindWithActionIndex> m_NtfyActionIndexArray;
};

} /* namespace ComfortableWindows */

#endif /* CBASEWINDOW_H_ */
