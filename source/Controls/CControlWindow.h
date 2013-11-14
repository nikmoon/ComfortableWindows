/*
 * CControlWindow.h
 *
 *  Created on: 08 но€б. 2013 г.
 *      Author: karpachevnk
 */

#ifndef CCONTROLWINDOW_H_
#define CCONTROLWINDOW_H_

#include "../CBaseWindow.h"

namespace ComfortableWindows
{

class CControlWindow: public CBaseWindow
{
public:
	CControlWindow(LPCTSTR _clname, DWORD _style, DWORD _exstyle, LPCTSTR _text, CBaseWindow *_parent, UINT _id, HINSTANCE _hinst,
		const SWindowRect &_rect);

	static void BeginControlGroup() { sm_BeginGroup = WS_GROUP|WS_TABSTOP; };

private:
	static DWORD sm_BeginGroup;
};

} /* namespace ComfortableWindows */

#endif /* CCONTROLWINDOW_H_ */
