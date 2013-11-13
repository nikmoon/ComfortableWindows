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


#undef GetClassName

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
//	Базовый класс оконной библиотеки
//
class CBaseWindow
{
public:
	CBaseWindow(LPCTSTR _clname, DWORD _style, DWORD _exstyle, LPCTSTR _title, CBaseWindow *_parent, HMENU _hmenu,
		HINSTANCE _hinst, const SWindowRect &_rect, LPVOID _pdata = NULL);

	virtual ~CBaseWindow();


	static void Binding(HWND _hwnd, CBaseWindow *_obj) { ::SetWindowLongPtr(_hwnd, GWLP_USERDATA, (LONG_PTR)_obj); };
	static WNDPROC InitSubclassing(HWND _hwnd, WNDPROC _proc) { return (WNDPROC)::SetWindowLongPtr(_hwnd, GWLP_WNDPROC, (LONG_PTR)_proc); };
	static WNDPROC DoneSubclassing(HWND _hwnd, WNDPROC _baseproc) { return InitSubclassing(_hwnd, _baseproc); };

	static CBaseWindow *GetObjectPtr(HWND _hwnd) { return (CBaseWindow*)::GetWindowLongPtr(_hwnd, GWLP_USERDATA); };
	static WNDPROC GetWndProc(HWND _hwnd) { return (WNDPROC)::GetWindowLongPtr(_hwnd, GWLP_WNDPROC); };


	HWND GetHWnd()			{ return m_hWnd; };
	HINSTANCE GetHInst()	{ return m_hInst; };
	LPCTSTR GetClassName()	{ return m_ClassName.c_str(); };
	CBaseWindow *GetParentWindow() { return m_pParent; };

	void Show() 			{ ::ShowWindow(m_hWnd, SW_SHOW); };
	void Hide() 			{ ::ShowWindow(m_hWnd, SW_HIDE); };
	void UpdateContent() 	{ ::UpdateWindow(m_hWnd); };
	void Destroy() 			{ ::DestroyWindow(m_hWnd); };

	static LRESULT CALLBACK BaseWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
	virtual LRESULT OnMessageDefault(UINT msg, WPARAM wp, LPARAM lp);
	virtual LRESULT OnMessage(UINT msg, WPARAM wp, LPARAM lp);
	virtual LRESULT OnPaint(UINT msg, WPARAM wp, LPARAM lp);
	virtual LRESULT OnDestroy(UINT msg, WPARAM wp, LPARAM lp);

private:
	HINSTANCE m_hInst;
	HWND m_hWnd;
	string m_ClassName;
	CBaseWindow *m_pParent;

};

} /* namespace ComfortableWindows */

#endif /* CBASEWINDOW_H_ */
