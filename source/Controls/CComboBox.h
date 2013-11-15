/*
 * CComboBox.h
 *
 *  Created on: 15 но€б. 2013 г.
 *      Author: karpachevnk
 */

#ifndef CCOMBOBOX_H_
#define CCOMBOBOX_H_

#include "CControlWindow.h"

namespace ComfortableWindows
{

enum EComboBoxType : DWORD
{
	ECT_COMBOBOX = CBS_SIMPLE
};

class CComboBox// : public CControlWindow
{
public:
	CComboBox();
	virtual ~CComboBox();
};

} /* namespace ComfortableWindows */

#endif /* CCOMBOBOX_H_ */
