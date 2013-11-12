/*
 * CControlWindow.cpp
 *
 *  Created on: 08 нояб. 2013 г.
 *      Author: karpachevnk
 */

#include "CControlWindow.h"

namespace ComfortableWindows
{

//
//		Массив данных для создания предпределенных элементов управления
//
SControlTypeInfo
CControlWindow::m_ControlClasses[]
{
		{"Button", BS_PUSHBUTTON},					// ECT_BUTTON
		{"Button", BS_AUTOCHECKBOX|BS_PUSHLIKE},	// ECT_FIXBUTTON
		{"Button", BS_CHECKBOX},					// ECT_CHECKBOX
		{"Button", BS_AUTOCHECKBOX},				// ECT_AUTOCHECKBOX
		{"Button", BS_3STATE},						// ECT_CHECKBOX3STATE
		{"Button", BS_AUTO3STATE}					// ECT_AUTOCHECKBOX3STATE
};


//
//		Флаг, определяющий первый элемент группы
//		Установлен при запуске приложения (загрузке модуля)
//		Автоматически сбрасывается при создании любого элемента
//
DWORD
CControlWindow::m_BeginGroup = WS_GROUP|WS_TABSTOP;


CControlWindow::CControlWindow(EControlType _type, DWORD _exstyle, LPCTSTR _text, CBaseWindow *_parent, UINT _id,
	HINSTANCE _hinst, const SWindowRect &_rect)
	: CChildWindow(m_ControlClasses[_type].m_CtrlClassName,m_ControlClasses[_type].m_CtrlStyle|m_BeginGroup,_exstyle,_text,_parent,_id,_hinst,_rect,NULL)
{
	// если текущий элемент стал началом группы, флаг надо сбросить
	m_BeginGroup ^= m_BeginGroup;
}


} /* namespace ComfortableWindows */
