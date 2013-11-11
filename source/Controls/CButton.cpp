/*
 * CButton.cpp
 *
 *  Created on: 08 но€б. 2013 г.
 *      Author: karpachevnk
 */

#include "CButton.h"

namespace ComfortableWindows
{

CButton::CButton(LPCTSTR _text, UINT _id, HINSTANCE _hinst, CBaseWindow *_parent, SWindowRect &_rect)
	: CControlWindow("Button",BS_PUSHBUTTON,0,_text,_parent,_id,_hinst,_rect)
{

}


CFixButton::CFixButton(LPCTSTR _text, UINT _id, HINSTANCE _hinst, CBaseWindow *_parent, SWindowRect &_rect)
	: CControlWindow("Button",BS_AUTOCHECKBOX|BS_PUSHLIKE,0,_text,_parent,_id,_hinst,_rect)
{

}

} /* namespace ComfortableWindows */
