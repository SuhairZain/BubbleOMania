/*
 * HighScoresPage.h
 *
 *  Created on: Apr 24, 2014
 *      Author: SuhairZain
 */

#ifndef HIGHSCORESPAGE_H_
#define HIGHSCORESPAGE_H_

#include <bb/cascades/AbsoluteLayout>
#include <bb/cascades/AbsoluteLayoutProperties>
#include <bb/cascades/Container>
#include <bb/cascades/CustomControl>
#include <bb/cascades/DockLayout>
#include <bb/cascades/ImageButton>
#include <bb/cascades/ImageView>
#include <bb/cascades/Label>
#include <bb/cascades/OrientationSupport>

using namespace bb::cascades;

class HighScoresPage: public CustomControl
{
	Q_OBJECT
signals:
	void goBack();
	void shareAllHighScores();
private slots:
	void handleOrientationChange();
public:
	HighScoresPage(int, int, int);
private:
	Container *rootC;
};

#endif /* HIGHSCORESPAGE_H_ */
