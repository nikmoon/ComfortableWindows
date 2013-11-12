/*
 * CButton.cpp
 *
 *  Created on: 08 но€б. 2013 г.
 *      Author: karpachevnk
 */

#include "CButton.h"

namespace ComfortableWindows
{

CButton::CButton(EControlType _type, LPCTSTR _text, UINT _id, HINSTANCE _hinst, CBaseWindow *_parent, const SWindowRect &_rect)
	: CControlWindow(_type, 0, _text,_parent,_id,_hinst,_rect)
{

}


} /* namespace ComfortableWindows */
