/*
 * MovingBG.cpp
 *
 *  Created on: Apr 23, 2014
 *      Author: SuhairZain
 */

#include "MovingBG.h"

MovingBG::MovingBG()
{
	ImageView *first = ImageView::create().
			layoutProperties(AbsoluteLayoutProperties::create().x(0.0f)).
			image("asset:///images/BG/clouds.png");

	ImageView *second = ImageView::create().
			layoutProperties(AbsoluteLayoutProperties::create().x(1280.0f)).
			image("asset:///images/BG/clouds.png");

	Container *rootC = Container::create().
			layout(AbsoluteLayout::create()).
			add(first).
			add(second);
	rootC->setMinWidth(1280.0f*2);

	TranslateTransition *move = TranslateTransition::create(rootC).
			duration(18000).
			easingCurve(StockCurve::Linear).
			toX(-1280.0f);

	TranslateTransition *reset = TranslateTransition::create(rootC).
			duration(0).
			toX(0.0f);

	SequentialAnimation *moveAndReset = SequentialAnimation::create(rootC).
			parent(this).
			repeatCount(100).
			//repeatCount(AnimationRepeatCount::Forever).
			add(move).
			add(reset);
	//moveAndReset->setRepeatCount(AnimationRepeatCount::Forever);
	moveAndReset->play();

	setRoot(rootC);
}
