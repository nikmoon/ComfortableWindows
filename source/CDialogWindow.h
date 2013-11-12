/*
 * CDialogWindow.h
 *
 *  Created on: 11 но€б. 2013 г.
 *      Author: karpachevnk
 */

#ifndef CDIALOGWINDOW_H_
#define CDIALOGWINDOW_H_

#include "COwnerWindow.h"
#include "Controls/CButton.h"

namespace ComfortableWindows
{

class CDialogWindow : public COwnerWindow
{
public:
	CDialogWindow(ETopLevelWindowStyle _style, DWORD _exstyle, LPCTSTR _title, CBaseWindow *_parent, HMENU _hmenu,
			HINSTANCE _hinst, const SWindowRect &_rect, LPVOID _pdata = NULL);

};

} /* namespace ComfortableWindows */

#endif /* CDIALOGWINDOW_H_ */
