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


enum EControlType
{
	ECT_BUTTON = 0,
	ECT_FIXBUTTON = 1,
	ECT_CHECKBOX = 2,
	ECT_AUTOCHECKBOX = 3,
	ECT_CHECKBOX3STATE = 4,
	ECT_AUTOCHECKBOX3STATE = 5
};


struct SControlTypeInfo
{
	LPCTSTR m_CtrlClassName;
	DWORD m_CtrlStyle;
};


class CControlWindow: public CChildWindow
{
public:
	CControlWindow(EControlType _type, DWORD _exstyle, LPCTSTR _text, CBaseWindow *_parent, UINT _id, HINSTANCE _hinst,
		SWindowRect &_rect);

	static void BeginControlGroup() { m_BeginGroup = WS_GROUP|WS_TABSTOP; };

	static SControlTypeInfo m_ControlClasses[];	// массив с информацией о типах элементов, доступных дл€ создани€

private:
	static DWORD m_BeginGroup;
};

} /* namespace ComfortableWindows */

#endif /* CCONTROLWINDOW_H_ */
