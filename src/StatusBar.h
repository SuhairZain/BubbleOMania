/*
 * StatusBar.h
 *
 *  Created on: Apr 2, 2014
 *      Author: SuhairZain
 */

#ifndef STATUSBAR_H_
#define STATUSBAR_H_

//#include "MyLCDNumber.h"

#include <bb/cascades/Color>
#include <bb/cascades/Container>
#include <bb/cascades/CustomControl>
#include <bb/cascades/DockLayout>
#include <bb/cascades/ImageButton>
#include <bb/cascades/ImageView>
#include <bb/cascades/Label>
#include <bb/cascades/OrientationSupport>
#include <bb/cascades/StackLayout>
#include <bb/cascades/StackLayoutProperties>
#include <bb/cascades/TextStyle>

using namespace bb::cascades;

class StatusBar: public CustomControl
{
	Q_OBJECT
signals:
	void pauseGame();
	void timeout(int, int);
private slots:
	void handleOrientationChange(bb::cascades::UIOrientation::Type);
	void handleResume();
	void pauseTimer();
	void resetTimer(int);
	void updateTime();
public:
	StatusBar(int);
	void updateCounter();
private:
	Container *rootC;
	Label *gameCounter, *timeCounter;
	QTimer *gameTimer;

	int count, time, nISOTB;
};

#endif /* STATUSBAR_H_ */
