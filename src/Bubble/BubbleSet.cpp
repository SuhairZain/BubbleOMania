/*
 * BubbleSet.cpp
 *
 *  Created on: Apr 1, 2014
 *      Author: SuhairZain
 */

#include "BubbleSet.h"
#include "time.h"

#include "Bubble.h"

BubbleSet::BubbleSet(int reqSetNumber, int reqShape)
{
	JsonDataAccess jda;
	QVariant list = jda.load(QDir::currentPath() + "/app/native/assets/savedShapes.json");
	QVariantList tempList = list.toList().at(reqShape).toList();

	//player = new MediaPlayer(this);
	//player->setSpeed(0.5);
	//player->setSourceUrl(QUrl("asset:///audio/tap.wav"));

	nZero = nNonZero = nTaps = 0;

	srand(time(NULL));

	nRows=tempList.size();
	int i, j;

	nCount = new int[nRows];

	for(i=0; i<nRows; i++)
		nCount[i] = tempList.at(i).toInt();
	/*nCount[0] = 3;
	nCount[1] = 5;
	nCount[2] = 6;
	nCount[3] = 7;
	nCount[4] = 8;
	nCount[5] = 7;
	nCount[6] = 6;
	nCount[7] = 5;
	nCount[8] = 3;*/

	//int nRows=8, nCols=4;

	//int nRows;

	/*do
	{
		nRows = rand()%10;
	}while(nRows<=3);

	do
	{
		nCols = rand()%7;
	}while(nCols<=2);*/

	//TODO
	//nRows = 13;
	//nCols = 8;

	/*if(OrientationSupport::instance()->orientation()==UIOrientation::Landscape)
	{
	[3, 5, 6, 7, 8, 7, 6, 5, 3]
		int t = nRows;
		nRows = nCols;
		nCols = t;
	}*/

	//nRows = nRows;
	//this->nCols = nCols;

	Container *rootC = Container::create();

	/*bubbles = new Bubble *[nRows];
	for(i=0; i<nRows; i++)
	{
		bubbles[i] = new Bubble[nCols];
	}*/
	//if(OrientationSupport::instance()->orientation()==UIOrientation::Portrait)
	//{
	maxCount=0;
	for(i=0; i<nRows; i++)
	{
		if(nCount[i]>maxCount)
			maxCount = nCount[i];

		Container *temp = Container::create().
				horizontal(HorizontalAlignment::Center).
				layout(StackLayout::create().orientation(LayoutOrientation::LeftToRight));

		for(j=0; j<nCount[i]; j++)
		{
			Bubble *bubble = new Bubble(reqSetNumber);

			if(bubble->isZero())
				nZero++;
			else
				nNonZero++;

			connect(bubble, SIGNAL(changedToZero(bool)), this, SLOT(handleChangeToZero(bool)));

			temp->add(bubble);

			if(j!=nCount[i]-1)
				bubble->setRightMargin(2.0f);
		}

		rootC->add(temp);

		if(i!=nRows-1)
			temp->setBottomMargin(2.0f);
	}
	/*}
	else
	{
		int maxCount=0;
		for(i=0; i<nRows; i++)
			if(nCount[i]>maxCount)
				maxCount=nCount[i];

		rootC->setLayout(StackLayout::create().orientation(LayoutOrientation::LeftToRight));

		for(i=0; i<nRows; i++)
		{
			Container *temp = Container::create().
					vertical(VerticalAlignment::Center);

			for(j=0; j<nCount[i]; j++)
			{
				Bubble *bubble = new Bubble(reqSetNumber);

				if(bubble->isZero())
					nZero++;
				else
					nNonZero++;

				connect(bubble, SIGNAL(changedToZero(bool)), this, SLOT(handleChangeToZero(bool)));

				temp->add(bubble);

				if(j!=nCount[i]-1)
					bubble->setBottomMargin(2.0f);
			}

			rootC->add(temp);

			if(i!=nRows-1)
				temp->setRightMargin(2.0f);

			//setVerticalAlignment(VerticalAlignment::Bottom);
		}
	}*/
	setRoot(rootC);

	nMinCount = nZero<nNonZero?nZero:nNonZero;
}

BubbleSet::~BubbleSet()
{
	delete [] nCount;
}

void BubbleSet::emitGameWonSignal()
{
	emit gameWonSignal();
}

void BubbleSet::gameWon()
{
	if(nTaps==nMinCount)
		emit achievement("ISOTB"); //I See Only The Best
	/*else if(nTaps==nMaxCount)
		emit achievement("EOTT"); //Eyes on the target*/
	else
		emit achievement("YJFTG"); //You just finished the game

	//player->setSourceUrl(QUrl("asset:///audio/won.mp3"));
	//player->play();

	int i, j;

	Container *rootC = static_cast<Container*>(root());
	Container *tempC;
	Bubble *tempBubble;

	for(i=0; i<nRows; i++)
	{
		tempC = static_cast<Container*>(rootC->at(i));
		for(j=0; j<nCount[i]; j++)
		{
			tempBubble = static_cast<Bubble*>(tempC->at(j));
			tempBubble->zoomOut();
		}
	}

	QTimer::singleShot(200, this, SLOT(emitGameWonSignal()));
}

int BubbleSet::getMaxCount()
{
	return maxCount;
}

void BubbleSet::handleChangeToZero(bool isZeroNow)
{
	//player->play();

	if(isZeroNow)
	{
		nZero++;
		nNonZero--;
	}
	else
	{
		nZero--;
		nNonZero++;
	}

	nTaps++;

	if(nZero==0 || nNonZero==0)
		gameWon();
}
