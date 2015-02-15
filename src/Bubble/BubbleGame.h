/*
 * BubbleGame.h
 *
 *  Created on: Apr 11, 2014
 *      Author: SuhairZain
 */

#ifndef BUBBLEGAME_H_
#define BUBBLEGAME_H_

#include "BubbleSet.h"
#include "../StatusBar.h"
#include "../TimerResetMessageHandler.h"

#include <QObject>
#include <bb/cascades/Container>
#include <bb/cascades/DockLayout>
//#include <bb/cascades/TranslateTransition>

using namespace bb::cascades;

class BubbleGame : public CustomControl
{
	Q_OBJECT
	signals:
	void pauseGame();
	void resumeGame();
	void timeout(int, int);

	private slots:
	void handleOrientationChange();
	void handleTimeout(int, int);
	void resetBubbleSet();

	public:
	BubbleGame();
	~BubbleGame();

	private:
	void resetOrder();
	void resetShapes();

	Container *rootC;
	ImageView *background;
	StatusBar *statusBar;
	TimerResetMessageHandler *resetMessageHandler;

	int number[8], counter;
	int *shapeNumber, shapeCount, shapeCounter;
};

#endif /* BUBBLEGAME_H_ */
