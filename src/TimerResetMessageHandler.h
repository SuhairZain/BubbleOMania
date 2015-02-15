/*
 * TimerResetMessageHandler.h
 *
 *  Created on: Apr 10, 2014
 *      Author: SuhairZain
 */

#ifndef TIMERRESETMESSAGEHANDLER_H_
#define TIMERRESETMESSAGEHANDLER_H_

//#include "TimerResetMessage.h"

#include <bb/cascades/Container>
#include <bb/cascades/CustomControl>
#include <bb/cascades/DockLayout>

using namespace bb::cascades;

class TimerResetMessageHandler: public CustomControl
{
	Q_OBJECT
signals:
	void resetTimerByVal(int);
private slots:
	void handleAchievement(QString);
	//void removeTimerResetMessage(TimerResetMessage*);
public:
	TimerResetMessageHandler();
	~TimerResetMessageHandler()
	{
		qDebug()<<"Deleting TRM Handler";
	}
private:
	Container *rootC;
};

#endif /* TIMERRESETMESSAGEHANDLER_H_ */
