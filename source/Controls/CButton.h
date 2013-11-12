/*
 * CButton.h
 *
 *  Created on: 08 но€б. 2013 г.
 *      Author: karpachevnk
 */

#ifndef CBUTTON_H_
#define CBUTTON_H_

#include "CControlWindow.h"
#include <windowsx.h>

namespace ComfortableWindows
{

class CButton : public CControlWindow
{
public:
	CButton(EControlType _type, LPCTSTR _text, UINT _id, HINSTANCE _hinst, CBaseWindow *_parent, const SWindowRect &_rect);
	void OnClick(int _aindex) { AddActionIndex(BN_CLICKED, _aindex); };
	bool IsChecked() { return (Button_GetCheck(GetHWnd()) == BST_CHECKED); };
};


typedef CButton CCheckBox;
typedef CButton CRadioButton;



} /* namespace ComfortableWindows */

#endif /* CBUTTON_H_ */
