/*
 * GameResult.h
 *
 *  Created on: Apr 4, 2014
 *      Author: SuhairZain
 */

#ifndef GAMERESULT_H_
#define GAMERESULT_H_

//#include <bb/cascades/Button>
#include <bb/cascades/AbsoluteLayout>
#include <bb/cascades/AbsoluteLayoutProperties>
#include <bb/cascades/Container>
#include <bb/cascades/CustomControl>
#include <bb/cascades/DockLayout>
#include <bb/cascades/ImageButton>
#include <bb/cascades/ImageView>
#include <bb/cascades/Label>
#include <bb/cascades/OrientationSupport>
#include <bb/cascades/TextStyle>

using namespace bb::cascades;

class GameResult: public CustomControl
{
	Q_OBJECT
signals:
	void goToHome();
	void goToNextGame();
	void shareHS(int);
private slots:
	void handleOrientationChange();
	void handleShareHS();
public:
	GameResult(int, int, int);

private:
	bool isLandscape;
	Container *rootC, *content, *innerContent;
	ImageView *boardHanger;

	int totalScore;
};

#endif /* GAMERESULT_H_ */
