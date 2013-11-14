/*
 * CButton.cpp
 *
 *  Created on: 08 но€б. 2013 г.
 *      Author: karpachevnk
 */

#include "CButton.h"

namespace ComfortableWindows
{

CButton::CButton(EButtonType _btype, LPCTSTR _text, UINT _id, HINSTANCE _hinst, CBaseWindow *_parent, const SWindowRect &_rect)
	: CControlWindow("BUTTON",_btype, 0, _text,_parent,_id,_hinst,_rect)
{

}



CCheckBox::CCheckBox(ECheckBoxType _cbtype, LPCTSTR _text, UINT _id, HINSTANCE _hinst, CBaseWindow *_parent, const SWindowRect &_rect)
	: CControlWindow("BUTTON",_cbtype, 0, _text,_parent,_id,_hinst,_rect)
{

}


CRadioButton::CRadioButton(ERadioButtonType _rbtype, LPCTSTR _text, UINT _id, HINSTANCE _hinst, CBaseWindow *_parent, const SWindowRect &_rect)
	: CControlWindow("BUTTON",_rbtype, 0, _text,_parent,_id,_hinst,_rect)
{

}


} /* namespace ComfortableWindows */
