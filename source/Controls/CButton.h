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
	CButton(LPCTSTR _text, UINT _id, HINSTANCE _hinst, CBaseWindow *_parent, SWindowRect &_rect);
};


class CFixButton : public CControlWindow
{
public:
	CFixButton(LPCTSTR _text, UINT _id, HINSTANCE _hinst, CBaseWindow *_parent, SWindowRect &_rect);
};

} /* namespace ComfortableWindows */

#endif /* CBUTTON_H_ */
