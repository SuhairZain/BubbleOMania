/*
 * BubbleSet.h
 *
 *  Created on: Apr 1, 2014
 *      Author: SuhairZain
 */

#ifndef BUBBLESET_H_
#define BUBBLESET_H_

#include <bb/cascades/Container>
#include <bb/cascades/CustomControl>
#include <bb/data/JsonDataAccess>
#include <bb/multimedia/MediaPlayer>
#include <bb/cascades/OrientationSupport>
#include <bb/cascades/StackLayout>

using namespace bb::cascades;
using namespace bb::data;
using namespace bb::multimedia;

class BubbleSet: public CustomControl
{
	Q_OBJECT
	signals:
	void gameWonSignal();
	void achievement(QString);
	private slots:
	void emitGameWonSignal();
	void handleChangeToZero(bool);
	public:
	BubbleSet(int, int);
	~BubbleSet();
	int getMaxCount();
	//~BubbleSet();
	private:
	void gameWon();

	//MediaPlayer *player;
	int nZero, nNonZero, nMinCount, nTaps;
	int nRows, *nCount;
	int maxCount;
};
#endif /* BUBBLESET_H_ */
