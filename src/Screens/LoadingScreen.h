/*
 * LoadingScreen.h
 *
 *  Created on: Apr 12, 2014
 *      Author: SuhairZain
 */

#ifndef LOADINGSCREEN_H_
#define LOADINGSCREEN_H_

//#include <bb/cascades/AbsoluteLayout>
#include <bb/cascades/Color>
#include <bb/cascades/Container>
#include <bb/cascades/CustomControl>
#include <bb/cascades/DockLayout>
#include <bb/cascades/ImageView>
#include <bb/cascades/OrientationSupport>
#include <bb/cascades/StockCurve>
#include <bb/cascades/TranslateTransition>

using namespace bb::cascades;

class LoadingScreen: public CustomControl
{
	Q_OBJECT
signals:
	void loadingDone();
private slots:
	void animationFinished();
public:
	LoadingScreen();
};

#endif /* LOADINGSCREEN_H_ */
