/*
 * CControlWindow.cpp
 *
 *  Created on: 08 но€б. 2013 г.
 *      Author: karpachevnk
 */

#include "CControlWindow.h"

namespace ComfortableWindows
{

//
//		‘лаг, определ€ющий первый элемент группы
//		”становлен при запуске приложени€ (загрузке модул€)
//		јвтоматически сбрасываетс€ при создании любого элемента
//
DWORD
CControlWindow::sm_BeginGroup = WS_GROUP|WS_TABSTOP;


CControlWindow::CControlWindow(
	LPCTSTR _clname,
	DWORD _style,
	DWORD _exstyle,
	LPCTSTR _text,
	CBaseWindow *_parent,
	UINT _id,
	HINSTANCE _hinst,
	const SWindowRect &_rect)
	: CBaseWindow(_clname,_style|WS_CHILD|sm_BeginGroup,_exstyle,_text,_parent,(HMENU)_id,_hinst,_rect,NULL)
{
	// если текущий элемент стал началом группы, флаг надо сбросить
	sm_BeginGroup ^= sm_BeginGroup;
}


} /* namespace ComfortableWindows */
