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

enum EButtonType : DWORD
{
	ECT_BUTTON = BS_PUSHBUTTON,
	ECT_BUTTON_FIXABLE = BS_AUTOCHECKBOX|BS_PUSHLIKE
};


enum ECheckBoxType : DWORD
{
	ECT_CHECKBOX = BS_CHECKBOX,
	ECT_CHECKBOX_AUTO = BS_AUTOCHECKBOX,
	ECT_CHECKBOX_3STATE = BS_3STATE,
	ECT_CHECKBOX_AUTO3STATE = BS_AUTO3STATE
};

enum ERadioButtonType : DWORD
{
	ECT_RADIOBUTTON = BS_RADIOBUTTON,
	ECT_RADIOBUTTON_AUTO = BS_AUTORADIOBUTTON
};


class CButton : public CControlWindow
{
public:
	CButton(EButtonType _btype, LPCTSTR _text, UINT _id, HINSTANCE _hinst, CBaseWindow *_parent, const SWindowRect &_rect);

	bool IsChecked() { return (Button_GetCheck(m_hWnd) == BST_CHECKED); };
	bool IsPushed() { return IsChecked(); };

	void OnClick(int _aindex) { SetActionIndex(BN_CLICKED, _aindex); };
};



class CCheckBox : public CButton
{
public:
	CCheckBox(ECheckBoxType _cbtype, LPCTSTR _text, UINT _id, HINSTANCE _hinst, CBaseWindow *_parent, const SWindowRect &_rect);
};


class CRadioButton : public CButton
{
public:
	CRadioButton(ERadioButtonType _rbtype, LPCTSTR _text, UINT _id, HINSTANCE _hinst, CBaseWindow *_parent, const SWindowRect &_rect);
};


class CGroupBox : public CButton
{
public:
	CGroupBox(LPCTSTR _title, UINT _id, HINSTANCE _hinst, CBaseWindow *_parent, const SWindowRect &_rect);
};


} /* namespace ComfortableWindows */

#endif /* CBUTTON_H_ */
