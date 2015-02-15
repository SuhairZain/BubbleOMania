/*
 * GameResult.cpp
 *
 *  Created on: Apr 4, 2014
 *      Author: SuhairZain
 */

#include "GameResult.h"
#define levelPoints 100
#define bonusPoints 50

GameResult::GameResult(int nISOTB, int level, int placeSecured)
{
	Container *finalContent = Container::create().
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Center);

	totalScore = 0;
	isLandscape = FALSE;

	ImageView *BG = ImageView::create().
			horizontal(HorizontalAlignment::Fill).
			vertical(VerticalAlignment::Fill).
			image("asset:///images/BG/scoreCardBG.png");


	if(placeSecured!=0)
	{
		ImageView *star = ImageView::create().
				horizontal(HorizontalAlignment::Center);
		if(placeSecured==1)
			star->setImage("asset:///images/highScore/gold.png");
		else if(placeSecured==2)
			star->setImage("asset:///images/highScore/silver.png");
		else
			star->setImage("asset:///images/highScore/bronze.png");
		finalContent->add(star);

		ImageView *text = ImageView::create().
				horizontal(HorizontalAlignment::Center).
				image("asset:///images/highScore/newHS.png");
		finalContent->add(text);
	}

	TextStyle style;
	style.setColor(Color::White);
	style.setFontSize(FontSize::Large);
	style.setTextAlign(TextAlign::Justify);

	totalScore = (level-1)*levelPoints + nISOTB*bonusPoints;

	Label *result = Label::create().
			horizontal(HorizontalAlignment::Center).
			multiline(TRUE).
			text("Games won: " + QString::number(level-1) +
					"\nBonuses: " + QString::number(nISOTB) +
					"\nTotal score: " + QString::number(totalScore)).
					textStyle(style);

	boardHanger = ImageView::create().
			image("asset:///images/resultBoard/768.png");

	ImageView *boardBG = ImageView::create().
			layoutProperties(AbsoluteLayoutProperties::create().position(155.0f, 55.0f)).
			image("asset:///images/resultBoard/BG.png");

	ImageView *board1 = ImageView::create().
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Center).
			image("asset:///images/resultBoard/1.png");

	Container *textC = Container::create().
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Center).
			add(result);

	Container *boardTextC = Container::create().
			layout(DockLayout::create()).
			layoutProperties(AbsoluteLayoutProperties::create().position(162.0f, 150.0f)).
			add(board1).
			add(textC);

	ImageButton *board2 = ImageButton::create().
			layoutProperties(AbsoluteLayoutProperties::create().position(162.0f, 382.0f)).
			defaultImage("asset:///images/resultBoard/2.png").
			pressedImage("asset:///images/resultBoard/2.png").
			connect(SIGNAL(clicked()), this, SLOT(handleShareHS()));

	ImageButton *board3 = ImageButton::create().
			layoutProperties(AbsoluteLayoutProperties::create().position(162.0f, 492.0f)).
			defaultImage("asset:///images/resultBoard/3.png").
			pressedImage("asset:///images/resultBoard/3.png").
			connect(SIGNAL(clicked()), this, SIGNAL(goToNextGame()));

	ImageButton *board4 = ImageButton::create().
			layoutProperties(AbsoluteLayoutProperties::create().position(160.0f, 609.0f)).
			defaultImage("asset:///images/resultBoard/4.png").
			pressedImage("asset:///images/resultBoard/4.png").
			connect(SIGNAL(clicked()), this, SIGNAL(goToHome()));

	innerContent = Container::create().
			layout(AbsoluteLayout::create()).
			layoutProperties(AbsoluteLayoutProperties::create()).
			add(boardBG).
			add(boardTextC).
			add(board2).
			add(board3).
			add(board4);

	content = Container::create().
			horizontal(HorizontalAlignment::Center).
			layout(AbsoluteLayout::create()).
			add(boardHanger).
			add(innerContent);

	finalContent->add(content);

	rootC = Container::create().
			layout(DockLayout::create()).
			preferredSize(768.0f, 1280.0f).
			add(BG).
			add(finalContent);

	if(OrientationSupport::instance()->orientation()==UIOrientation::Landscape)
	{
		AbsoluteLayoutProperties *temp = static_cast<AbsoluteLayoutProperties*>(innerContent->layoutProperties());
		temp->setPositionX(254.0f);
		boardHanger->setImage("asset:///images/resultBoard/1280.png");
		isLandscape = TRUE;
		rootC->setPreferredSize(1280.0f, 768.0f);
		content->setVerticalAlignment(VerticalAlignment::Top);
	}

	connect(OrientationSupport::instance(), SIGNAL(orientationAboutToChange(bb::cascades::UIOrientation::Type)), this, SLOT(handleOrientationChange()));

	setRoot(rootC);
}

void GameResult::handleOrientationChange()
{
	if(isLandscape)
	{
		content->setVerticalAlignment(VerticalAlignment::Center);
		AbsoluteLayoutProperties *temp = static_cast<AbsoluteLayoutProperties*>(innerContent->layoutProperties());
		temp->setPositionX(0.0f);
		isLandscape = FALSE;
		boardHanger->setImage("asset:///images/resultBoard/768.png");
	}
	else
	{
		content->setVerticalAlignment(VerticalAlignment::Top);
		AbsoluteLayoutProperties *temp = static_cast<AbsoluteLayoutProperties*>(innerContent->layoutProperties());
		temp->setPositionX(254.0f);
		isLandscape = TRUE;
		boardHanger->setImage("asset:///images/resultBoard/1280.png");
	}

	float temp = rootC->preferredWidth();
	rootC->setPreferredWidth(rootC->preferredHeight());
	rootC->setPreferredHeight(temp);
}

void GameResult::handleShareHS()
{
	emit shareHS(totalScore);
}
