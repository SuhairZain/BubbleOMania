/*
 * TimerResetMessageHandler.cpp
 *
 *  Created on: Apr 10, 2014
 *      Author: SuhairZain
 */

#include "TimerResetMessageHandler.h"

TimerResetMessageHandler::TimerResetMessageHandler()
{
	rootC = Container::create().
			layout(DockLayout::create()).
			preferredSize(768.0f, 150.0f);

	rootC->setOverlapTouchPolicy(OverlapTouchPolicy::Allow);

	setRoot(rootC);
}

void TimerResetMessageHandler::handleAchievement(QString type)
{
	//TimerResetMessage *message;
	int resetVal;

	if(type=="ISOTB")
	{
		resetVal = 3;
		//message = new TimerResetMessage(resetVal, "Eyes On The Target");
	}
	else
	{
		resetVal = 1;
		//message = new TimerResetMessage(resetVal, "You just finished the game");
	}
	/*message = new TimerResetMessage(resetVal, type);
	message->setHorizontalAlignment(HorizontalAlignment::Center);
	message->setVerticalAlignment(VerticalAlignment::Center);
	message->setOverlapTouchPolicy(OverlapTouchPolicy::Allow);*/
	emit resetTimerByVal(resetVal);

	//connect(message, SIGNAL(ended(TimerResetMessage*)), this, SLOT(removeTimerResetMessage(TimerResetMessage*)));

	//rootC->add(message);
}

/*void TimerResetMessageHandler::removeTimerResetMessage(TimerResetMessage *temp)
{
	rootC->remove(temp);
	delete temp;
}*/
