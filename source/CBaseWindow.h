/*
 * CBaseWindow.h
 *
 *  Created on: 05 но€б. 2013 г.
 *      Author: karpachevnk
 */

#ifndef CBASEWINDOW_H_
#define CBASEWINDOW_H_

#include <windows.h>
#include <string>
#include <vector>

using namespace std;

namespace ComfortableWindows
{

struct SWindowRect
{
	int x, y, cx, cy;
};


class CBaseWindow
{
public:
	CBaseWindow(LPCTSTR _clname, DWORD _style, DWORD _exstyle, LPCTSTR _title, CBaseWindow *_parent, HMENU _hmenu,
		HINSTANCE _hinst, SWindowRect &_rect, LPVOID _pdata = NULL);

	virtual ~CBaseWindow();


	static void SetWndPtr(HWND _hwnd, CBaseWindow *_obj);
	static WNDPROC SetWndProc(HWND _hwnd, WNDPROC _proc);
	static CBaseWindow *GetWndPtr(HWND _hwnd);
	static WNDPROC GetWndProc(HWND _hwnd);


	HWND GetHWnd()			{ return m_hWnd; };
	HINSTANCE GetHInst()	{ return m_hInst; };
	LPCTSTR GetClassName()	{ return m_ClassName.c_str(); };
	CBaseWindow *GetParentWindow() { return m_pParent; };

	void Show() 			{ ::ShowWindow(m_hWnd, SW_SHOW); };
	void Hide() 			{ ::ShowWindow(m_hWnd, SW_HIDE); };
	void UpdateContent() 	{ ::UpdateWindow(m_hWnd); };
	void Destroy() 			{ ::DestroyWindow(m_hWnd); };

	static LRESULT CALLBACK BaseWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
	virtual LRESULT OnMessage(UINT msg, WPARAM wp, LPARAM lp);
	virtual LRESULT OnMessageDefault(UINT msg, WPARAM wp, LPARAM lp) { return ::DefWindowProc(m_hWnd, msg, wp, lp); };
	virtual LRESULT OnDestroy() { return OnMessageDefault(WM_DESTROY, 0, 0); };
	virtual LRESULT OnClose() { return OnMessageDefault(WM_CLOSE, 0, 0); };

private:
	HINSTANCE m_hInst;
	HWND m_hWnd;
	string m_ClassName;
	CBaseWindow *m_pParent;

};

} /* namespace ComfortableWindows */

#endif /* CBASEWINDOW_H_ */
