/*
 * IView.h
 *
 *  Created on: Jul 25, 2014
 *      Author: bastl
 */

#include "BastlDef.h"
#if defined(BASTL_FEATURE_ALL)

#ifndef IVIEW_H_
#define IVIEW_H_

class IView {
public:
	virtual ~IView() = 0;
	virtual void update() = 0;
};

inline IView::~IView() { }

#endif /* IVIEW_H_ */

#endif // defined(BASTL_FEATURE_ALL)
