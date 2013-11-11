/*
 * CButton.h
 *
 *  Created on: 08 но€б. 2013 г.
 *      Author: karpachevnk
 */

#ifndef CBUTTON_H_
#define CBUTTON_H_

#include "CControlWindow.h"

namespace ComfortableWindows
{

class CButton : public CControlWindow
{
public:
	CButton(EControlType _type, LPCTSTR _text, UINT _id, HINSTANCE _hinst, CBaseWindow *_parent, SWindowRect &_rect);
};


typedef CButton CCheckBox;
typedef CButton CRadioButton;



} /* namespace ComfortableWindows */

#endif /* CBUTTON_H_ */
