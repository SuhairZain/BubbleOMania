/*
 * BubbleGame.cpp
 *
 *  Created on: Apr 11, 2014
 *      Author: SuhairZain
 */

#include "BubbleGame.h"
#include "time.h"

BubbleGame::BubbleGame()
{
	//OrientationSupport::instance()->setSupportedDisplayOrientation(SupportedDisplayOrientation::CurrentLocked);

	background = ImageView::create().
			horizontal(HorizontalAlignment::Fill).
			vertical(VerticalAlignment::Fill).
			image("asset:///images/BG/BG.png");

	resetMessageHandler = new TimerResetMessageHandler;
	/*resetMessageHandler->setHorizontalAlignment(HorizontalAlignment::Center);
	resetMessageHandler->setVerticalAlignment(VerticalAlignment::Center);
	resetMessageHandler->setOverlapTouchPolicy(OverlapTouchPolicy::Allow);*/

	statusBar = new StatusBar(10);
	statusBar->setHorizontalAlignment(HorizontalAlignment::Center);
	statusBar->setVerticalAlignment(VerticalAlignment::Top);
	connect(statusBar, SIGNAL(pauseGame()), this, SIGNAL(pauseGame()));
	connect(statusBar, SIGNAL(timeout(int, int)), this, SLOT(handleTimeout(int, int)));
	connect(this, SIGNAL(resumeGame()), statusBar, SLOT(handleResume()));

	connect(resetMessageHandler, SIGNAL(resetTimerByVal(int)), statusBar, SLOT(resetTimer(int)));

	counter = -1;
	for(int i=0; i<8; i++)
		number[i] = i;
	resetOrder();

	bb::data::JsonDataAccess jda;
	QVariant list = jda.load(QDir::currentPath() + "/app/native/assets/savedShapes.json");

	shapeCount = list.toList().size();

	shapeNumber = new int[shapeCount];
	shapeCounter = -1;
	for(int i=0; i<shapeCount; i++)
		shapeNumber[i] = i;
	resetShapes();

	BubbleSet *bubbleSet = new BubbleSet(number[++counter], shapeNumber[++shapeCounter]);
	bubbleSet->setObjectName("bubbleSet");
	bubbleSet->setHorizontalAlignment(HorizontalAlignment::Center);
	bubbleSet->setVerticalAlignment(VerticalAlignment::Center);
	connect(bubbleSet, SIGNAL(gameWonSignal()), this, SLOT(resetBubbleSet()));
	connect(bubbleSet, SIGNAL(achievement(QString)), resetMessageHandler, SLOT(handleAchievement(QString)));

	rootC = Container::create().
			layout(DockLayout::create()).
			preferredSize(768.0f, 1280.0f).
			add(background).
			add(statusBar).
			add(bubbleSet);//.
			//add(resetMessageHandler);

	//OrientationSupport::instance()->setSupportedDisplayOrientation(SupportedDisplayOrientation::All);

	if(OrientationSupport::instance()->orientation()==UIOrientation::Landscape)
	{
		rootC->setPreferredSize(1280.0f, 768.0f);
		bubbleSet->setVerticalAlignment(VerticalAlignment::Bottom);
		bubbleSet->setRotationZ(-90.0f);
	}

	setRoot(rootC);
	connect(OrientationSupport::instance(), SIGNAL(orientationAboutToChange(bb::cascades::UIOrientation::Type)), this, SLOT(handleOrientationChange()));
}

BubbleGame::~BubbleGame()
{
	delete [] shapeNumber;
	delete resetMessageHandler;
}

void BubbleGame::handleOrientationChange()
{
	float temp = rootC->preferredWidth();
	rootC->setPreferredWidth(rootC->preferredHeight());
	rootC->setPreferredHeight(temp);

	BubbleSet *tempControl = static_cast<BubbleSet*>(rootC->findChild<Control*>("bubbleSet"));

	if(tempControl->rotationZ()==0.0f)
	{
		qDebug()<<tempControl->getMaxCount();
		if(tempControl->getMaxCount()>=7)
		{
			tempControl->setVerticalAlignment(VerticalAlignment::Bottom);
		}
		else
			tempControl->setVerticalAlignment(VerticalAlignment::Center);
		tempControl->setRotationZ(-90.0f);
	}
	else
	{
		tempControl->setVerticalAlignment(VerticalAlignment::Center);
		tempControl->setRotationZ(0.0f);
	}
}

void BubbleGame::handleTimeout(int nISOTB, int level)
{
	emit timeout(nISOTB, level);
}

void BubbleGame::resetBubbleSet()
{
	BubbleSet *bubbleSet = new BubbleSet(number[++counter], shapeNumber[++shapeCounter]);
	bubbleSet->setObjectName("bubbleSet");
	bubbleSet->setVerticalAlignment(VerticalAlignment::Center);
	bubbleSet->setHorizontalAlignment(HorizontalAlignment::Center);
	connect(bubbleSet, SIGNAL(gameWonSignal()), this, SLOT(resetBubbleSet()));
	//connect(OrientationSupport::instance(), SIGNAL(orientationAboutToChange(bb::cascades::UIOrientation::Type)), bubbleSet, SLOT(handleOrientationChange()));
	connect(bubbleSet, SIGNAL(achievement(QString)), resetMessageHandler, SLOT(handleAchievement(QString)));

	Control *temp = rootC->at(2);

	rootC->replace(2, bubbleSet);

	QTimer::singleShot(4000, temp, SLOT(deleteLater()));

	if(counter==7)
	{
		counter=-1;
		resetOrder();
	}

	if(shapeCounter==shapeCount-1)
	{
		shapeCounter=-1;
		resetShapes();
	}
}

void BubbleGame::resetOrder()
{
	srand(time(NULL));

	for(int i=0; i<8; i++)
	{
		int indexToSwap = rand()%8;

		int temp = number[i];
		number[i] = number[indexToSwap];
		number[indexToSwap] = temp;
	}
}

void BubbleGame::resetShapes()
{
	srand(time(NULL));

	for(int i=0; i<shapeCount; i++)
	{
		int indexToSwap = rand()%shapeCount;

		int temp = shapeNumber[i];
		shapeNumber[i] = shapeNumber[indexToSwap];
		shapeNumber[indexToSwap] = temp;
	}
}
