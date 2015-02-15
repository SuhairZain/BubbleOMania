/*
 * Bubble.h
 *
 *  Created on: Apr 1, 2014
 *      Author: SuhairZain
 */

#ifndef BUBBLE_H_
#define BUBBLE_H_

#include <bb/cascades/CustomControl>
#include <bb/cascades/FadeTransition>
#include <bb/cascades/ImageView>
#include <bb/cascades/ScaleTransition>
#include <bb/cascades/StockCurve>
#include <bb/cascades/TapHandler>

using namespace bb::cascades;

class Bubble: public CustomControl
{
	Q_OBJECT
	signals:
	void changedToZero(bool);
	void isZero(bool);
public:
	Bubble(int);
	bool isZero();
	void zoomOut();
	private slots:
	void handleTap();
	private:
	ImageView *root;
	ScaleTransition *zoomOutAnimation;

	bool zero;
	int setN;
};

#endif /* BUBBLE_H_ */
