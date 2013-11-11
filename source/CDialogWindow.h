/*
 * CDialogWindow.h
 *
 *  Created on: 11 но€б. 2013 г.
 *      Author: karpachevnk
 */

#ifndef CDIALOGWINDOW_H_
#define CDIALOGWINDOW_H_

#include "COwnerWindow.h"
#include "Controls/CControlWindow.h"
#include "Controls/CButton.h"

namespace ComfortableWindows
{

class CDialogWindow : public COwnerWindow
{
public:
	CDialogWindow(ETopLevelWindowStyle _style, DWORD _exstyle, LPCTSTR _title, CBaseWindow *_parent, HMENU _hmenu,
			HINSTANCE _hinst, SWindowRect &_rect, LPVOID _pdata = NULL);

	virtual LRESULT OnMessage(UINT msg, WPARAM wp, LPARAM lp);
	virtual LRESULT OnCommandFromControl(CControlWindow *pwin, DWORD note_code);

	virtual LRESULT OnCommandFromButton(CButton *pb, DWORD _ncode);
	virtual LRESULT OnCommandFromCheckbox(CCheckBox *chb, DWORD _ncode);

};

} /* namespace ComfortableWindows */

#endif /* CDIALOGWINDOW_H_ */
