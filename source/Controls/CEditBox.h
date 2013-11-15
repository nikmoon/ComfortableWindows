/*
 * CEditBox.h
 *
 *  Created on: 15 но€б. 2013 г.
 *      Author: karpachevnk
 */

#ifndef CEDITBOX_H_
#define CEDITBOX_H_

#include "CControlWindow.h"

namespace ComfortableWindows
{

enum EEditBoxType : DWORD
{
	ECT_EDITBOX = WS_BORDER,
	ECT_EDITBOX_HSCROLL = ECT_EDITBOX|ES_AUTOHSCROLL,
	ECT_EDITBOX_MULTILINE = WS_BORDER|ES_MULTILINE,
	ECT_EDITBOX_MULTILINE_HSCROLL = ECT_EDITBOX_MULTILINE|ES_AUTOHSCROLL,
	ECT_EDITBOX_MULTILINE_VSCROLL = ECT_EDITBOX_MULTILINE|ES_AUTOVSCROLL,
	ECT_EDITBOX_MULTILINE_ALLSCROLL = ECT_EDITBOX_MULTILINE|ES_AUTOHSCROLL|ES_AUTOVSCROLL
};

class CEditBox : public CControlWindow
{
public:
	CEditBox(EEditBoxType _ebtype, LPCTSTR _text, CBaseWindow *_parent, UINT _id, HINSTANCE _hinst, const SWindowRect &_rect);
//	LPCTSTR _clname, DWORD _style, DWORD _exstyle, LPCTSTR _text, CBaseWindow *_parent, UINT _id, HINSTANCE _hinst,
//			const SWindowRect &_rect);
	virtual ~CEditBox();
};

} /* namespace ComfortableWindows */

#endif /* CEDITBOX_H_ */
