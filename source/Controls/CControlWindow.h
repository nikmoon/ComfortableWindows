/*
 * CControlWindow.h
 *
 *  Created on: 08 но€б. 2013 г.
 *      Author: karpachevnk
 */

#ifndef CCONTROLWINDOW_H_
#define CCONTROLWINDOW_H_

#include "../CChildWindow.h"

namespace ComfortableWindows
{

class CControlWindow: public CChildWindow
{
public:
	CControlWindow(LPCTSTR _clname, DWORD _style, DWORD _exstyle, LPCTSTR _text, CBaseWindow *_parent, UINT _id,
		HINSTANCE _hinst, SWindowRect &_rect);

	static void BeginControlGroup() { m_BeginGroup = WS_GROUP|WS_TABSTOP; };

private:
	static DWORD m_BeginGroup;
};

} /* namespace ComfortableWindows */

#endif /* CCONTROLWINDOW_H_ */
