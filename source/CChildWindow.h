/*
 * CChildWindow.h
 *
 *  Created on: 07 нояб. 2013 г.
 *      Author: karpachevnk
 */

#ifndef CCHILDWINDOW_H_
#define CCHILDWINDOW_H_

#include "CBaseWindow.h"

namespace ComfortableWindows
{


struct SNotifyBindWithActionIndex
{
	WORD m_NotifyCode;
	int m_ActionIndex;
};


/*----------------------------------
 *		Дочернее окно
 ---------------------------------*/
class CChildWindow: public CBaseWindow
{
public:
	CChildWindow(LPCTSTR _clname, DWORD _style, DWORD _exstyle, LPCTSTR _text, CBaseWindow *_parent, UINT _id,
			HINSTANCE _hinst, const SWindowRect &_rect, LPVOID _pdata = NULL);

	UINT GetID() { return m_ID; };

	static void ShowOnCreate(bool _show) { if (_show) m_VisibleOnCreate = WS_VISIBLE; else m_VisibleOnCreate = 0; };

	void AddActionIndex(WORD _ntfycode, int _aindex);
	int aIndex(WORD _ntfycode);

private:
	UINT m_ID;	// идентификатор элемента

	CBaseWindow *CheckParent(CBaseWindow *_parent) { if (!_parent) throw(1); return _parent; };

	static DWORD m_VisibleOnCreate;

	vector<SNotifyBindWithActionIndex> m_NtfyActionIndex;
};


} /* namespace ComfortableWindows */

#endif /* CCHILDWINDOW_H_ */
