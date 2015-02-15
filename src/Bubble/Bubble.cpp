/*
 * Bubble.cpp
 *
 *  Created on: Apr 1, 2014
 *      Author: SuhairZain
 */

#include "Bubble.h"

Bubble::Bubble(int setNumber)
{
	setN = setNumber;
	zero = rand()%2;

	TapHandler *tapHandler = TapHandler::create().
			onTapped(this, SLOT(handleTap()));

	root = ImageView::create().
			opacity(0.0f).
			preferredSize(90.0f, 90.0f).
			image(Image("asset:///images/set" + QString::number(setNumber) + "/" + QString::number(zero) + ".png")).
			addGestureHandler(tapHandler);

	setRoot(root);

	FadeTransition *fadeIn = FadeTransition::create(root).
			parent(this).
			duration(300).
			to(1.0f);

	fadeIn->play();

	zoomOutAnimation = ScaleTransition::create(root).
			parent(this).
			toScale(0.0f).
			duration(200).
			easingCurve(StockCurve::Linear);
}

void Bubble::handleTap()
{
	zero = !zero;

	root->setImage(Image("asset:///images/set" + QString::number(setN) + "/" + QString::number(zero) + ".png"));

	emit changedToZero(zero);
}

bool Bubble::isZero()
{
	return zero;
}

void Bubble::zoomOut()
{
	zoomOutAnimation->play();
}
