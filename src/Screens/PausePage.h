/*
 * PausePage.h
 *
 *  Created on: Apr 23, 2014
 *      Author: SuhairZain
 */

#ifndef PAUSEPAGE_H_
#define PAUSEPAGE_H_

#include "MovingBG.h"

//QLCDNUMBER_H

#include <bb/cascades/AbsoluteLayout>
#include <bb/cascades/AbsoluteLayoutProperties>
#include <bb/cascades/Container>
#include <bb/cascades/CustomControl>
#include <bb/cascades/DockLayout>
#include <bb/cascades/ImageButton>
#include <bb/cascades/ImageView>
#include <bb/cascades/OrientationSupport>

using namespace bb::cascades;

class PausePage: public CustomControl
{
	Q_OBJECT
signals:
	void resume();
private slots:
	void handleOrientationChange();
public:
	PausePage();
private:
	Container *rootC;
};

#endif /* PAUSEPAGE_H_ */
