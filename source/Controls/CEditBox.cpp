/*
 * CEditBox.cpp
 *
 *  Created on: 15 ����. 2013 �.
 *      Author: karpachevnk
 */

#include "CEditBox.h"

namespace ComfortableWindows
{

CEditBox::CEditBox(
	EEditBoxType _ebtype,
	LPCTSTR _text,
	CBaseWindow *_parent,
	UINT _id,
	HINSTANCE _hinst,
	const SWindowRect &_rect)
	: CControlWindow("EDIT",_ebtype,0,_text,_parent,_id,_hinst,_rect)
{

}

CEditBox::~CEditBox()
{

}

} /* namespace ComfortableWindows */
