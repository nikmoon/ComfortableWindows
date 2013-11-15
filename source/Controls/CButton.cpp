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
	: CButton((EButtonType)_cbtype, _text, _id, _hinst, _parent, _rect)
{

}


CRadioButton::CRadioButton(ERadioButtonType _rbtype, LPCTSTR _text, UINT _id, HINSTANCE _hinst, CBaseWindow *_parent, const SWindowRect &_rect)
	: CButton((EButtonType)_rbtype, _text,_id, _hinst, _parent,_rect)
{

}

CGroupBox::CGroupBox(LPCTSTR _title, UINT _id, HINSTANCE _hinst, CBaseWindow *_parent, const SWindowRect &_rect)
	: CButton((EButtonType)BS_GROUPBOX, _title, _id, _hinst, _parent, _rect)
{

}


} /* namespace ComfortableWindows */
