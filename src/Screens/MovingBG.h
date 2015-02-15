/*
 * MovingBG.h
 *
 *  Created on: Apr 23, 2014
 *      Author: SuhairZain
 */

#ifndef MOVINGBG_H_
#define MOVINGBG_H_

#include <bb/cascades/AbsoluteLayout>
#include <bb/cascades/AbsoluteLayoutProperties>
#include <bb/cascades/AnimationRepeatCount>
#include <bb/cascades/Container>
#include <bb/cascades/CustomControl>
#include <bb/cascades/ImageView>
#include <bb/cascades/SequentialAnimation>
#include <bb/cascades/StockCurve>
#include <bb/cascades/TranslateTransition>

using namespace bb::cascades;

class MovingBG: public CustomControl
{
public:
	MovingBG();
};

#endif /* MOVINGBG_H_ */
