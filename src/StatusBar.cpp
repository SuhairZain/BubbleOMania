/*
 * StatusBar.cpp
 *
 *  Created on: Apr 2, 2014
 *      Author: SuhairZain
 */

#include "StatusBar.h"

StatusBar::StatusBar(int initial)
{
	time = initial+1;
	count = 1;
	nISOTB=0;

	gameTimer = new QTimer(this);
	gameTimer->setInterval(1000);
	connect(gameTimer, SIGNAL(timeout()), this, SLOT(updateTime()));
	gameTimer->start();

	int height = 74+12;

	TextStyle counterStyle;
	counterStyle.setFontSize(FontSize::XXLarge);
	counterStyle.setFontWeight(FontWeight::W300);

	gameCounter = Label::create().
			horizontal(HorizontalAlignment::Center).
			textStyle(counterStyle).
			text(QString::number(count));

	Container *gameC = Container::create().
			layoutProperties(StackLayoutProperties::create().spaceQuota(3.0f)).
			preferredHeight(height).
			add(gameCounter);

	ImageButton *pauseButton = ImageButton::create().
			defaultImage("asset:///images/statusBar/pause.png").
			pressedImage("asset:///images/statusBar/pausePressed.png").
			connect(SIGNAL(clicked()), this, SLOT(pauseTimer()));

	Container *pauseButtonC = Container::create().
			//background(Color::DarkGray).
			preferredSize(height, height).
			//layoutProperties(StackLayoutProperties::create().spaceQuota(1.0f)).
			add(pauseButton);

	QString tempChar;
	tempChar = initial%60<10?"0":"";

	timeCounter = Label::create().
			horizontal(HorizontalAlignment::Center).
			textStyle(counterStyle).
			text(QString::number(initial/60) + ":" + tempChar + QString::number(initial%60));

	Container *timeC = Container::create().
			layoutProperties(StackLayoutProperties::create().spaceQuota(3.0f)).
			preferredHeight(height).
			add(timeCounter);

	rootC = Container::create().
			preferredSize(1280.0f, height).
			//preferredWidth(768.0f).
			//background(Color::Red).
			layout(StackLayout::create().orientation(LayoutOrientation::LeftToRight)).
			//add(new MyLCDNumber).
			add(gameC).
			add(pauseButtonC).
			add(timeC);

	setRoot(rootC);
}

void StatusBar::handleOrientationChange(bb::cascades::UIOrientation::Type type)
{
	if(type==UIOrientation::Landscape)
	{

	}
}

void StatusBar::handleResume()
{
	gameTimer->start();
}

void StatusBar::pauseTimer()
{
	gameTimer->stop();

	emit pauseGame();
}

void StatusBar::resetTimer(int resetByVal)
{
	time += resetByVal;

	QString tempChar;
	tempChar = time%60<10?"0":"";
	timeCounter->setText(QString::number(time/60) + ":" + tempChar + QString::number(time%60));

	updateCounter();

	if(resetByVal==3)
		nISOTB++;
}

void StatusBar::updateCounter()
{
	count++;

	gameCounter->setText(QString::number(count));
}

void StatusBar::updateTime()
{
	time--;

	QString tempChar;
	tempChar = time%60<10?"0":"";
	timeCounter->setText(QString::number(time/60) + ":" + tempChar + QString::number(time%60));

	if(time==0)
		emit timeout(nISOTB, count);
}
