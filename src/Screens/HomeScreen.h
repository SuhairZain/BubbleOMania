/*
 * HomeScreen.h
 *
 *  Created on: Apr 11, 2014
 *      Author: SuhairZain
 */

#ifndef HOMESCREEN_H_
#define HOMESCREEN_H_

#include "MovingBG.h"

//#include <bb/cascades/Button>
#include <bb/cascades/Container>
#include <bb/cascades/CustomControl>
#include <bb/cascades/DockLayout>
#include <bb/cascades/ImageButton>
#include <bb/cascades/ImageView>
#include <bb/cascades/OrientationSupport>
//#include <bb/cascades/StockCurve>
//#include <bb/cascades/TranslateTransition>

using namespace bb::cascades;

class HomeScreen: public CustomControl
{
	Q_OBJECT
signals:
	void goToHelp();
	void goToHighScores();
	void goToInfo();
	void goToSettings();
	void startNewGame();
private slots:
	void handleOrientationChange();
public:
	HomeScreen();
	//void moveOut();
private:
	Container *rootC, *content;
	ImageView *logo;
};

#endif /* HOMESCREEN_H_ */
