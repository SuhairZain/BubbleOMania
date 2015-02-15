/*
 * HomeScreen.cpp
 *
 *  Created on: Apr 11, 2014
 *      Author: SuhairZain
 */

#include "HomeScreen.h"

HomeScreen::HomeScreen()
{
	ImageView *BG = ImageView::create().
			horizontal(HorizontalAlignment::Fill).
			vertical(VerticalAlignment::Fill).
			image("asset:///images/BG/homeScreenBG.png");

	MovingBG *movingBG = new MovingBG;
	movingBG->setHorizontalAlignment(HorizontalAlignment::Center);
	movingBG->setVerticalAlignment(VerticalAlignment::Top);

	ImageView *treeBG = ImageView::create().
			image("asset:///images/tree/treeBG.png");

	ImageButton *next = ImageButton::create().
			layoutProperties(AbsoluteLayoutProperties::create().position(15.0f, 147.0f)).
			defaultImage("asset:///images/tree/1.png").
			pressedImage("asset:///images/tree/1.png").
			connect(SIGNAL(clicked()), this, SIGNAL(startNewGame()));

	ImageButton *helpButton = ImageButton::create().
			layoutProperties(AbsoluteLayoutProperties::create().position(52.0f, 406.0f)).
			defaultImage("asset:///images/tree/2.png").
			pressedImage("asset:///images/tree/2.png").
			connect(SIGNAL(clicked()), this, SIGNAL(goToHelp()));

	ImageButton *infoButton = ImageButton::create().
			layoutProperties(AbsoluteLayoutProperties::create().position(362.0f, 428.0f)).
			defaultImage("asset:///images/tree/3.png").
			pressedImage("asset:///images/tree/3.png").
			connect(SIGNAL(clicked()), this, SIGNAL(goToInfo()));

	ImageButton *hsButton = ImageButton::create().
			layoutProperties(AbsoluteLayoutProperties::create().position(370.0f, 541.0f)).
			defaultImage("asset:///images/tree/4.png").
			pressedImage("asset:///images/tree/4.png").
			connect(SIGNAL(clicked()), this, SIGNAL(goToHighScores()));

	content = Container::create().
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Bottom).
			layout(AbsoluteLayout::create()).
			add(treeBG).
			add(next).
			add(helpButton).
			add(infoButton).
			add(hsButton);

	ImageView *grass = ImageView::create().
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Bottom).
			image("asset:///images/tree/grass.png");

	logo = ImageView::create().
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Top).
			image("asset:///images/logo.png");

	rootC = Container::create().
			layout(DockLayout::create()).
			preferredSize(768.0f, 1280.0f).
			//ty(-1280.0f).
			add(BG).
			add(movingBG).
			add(content).
			add(grass).
			add(logo);

	if(OrientationSupport::instance()->orientation()==UIOrientation::Landscape)
	{
		content->setHorizontalAlignment(HorizontalAlignment::Left);
		logo->setHorizontalAlignment(HorizontalAlignment::Right);
		logo->setVerticalAlignment(VerticalAlignment::Center);
		rootC->setPreferredSize(1280.0f, 768.0f);
		//rootC->setTranslationY(-768.0f);
	}

	/*TranslateTransition *moveIn = TranslateTransition::create(rootC).
			parent(this).
			duration(1000).
			easingCurve(StockCurve::BackOut).
			toY(0.0f);*/

	connect(OrientationSupport::instance(), SIGNAL(orientationAboutToChange(bb::cascades::UIOrientation::Type)), this, SLOT(handleOrientationChange()));

	setRoot(rootC);
	//moveIn->play();
}

void HomeScreen::handleOrientationChange()
{
	float temp = rootC->preferredWidth();
	rootC->setPreferredWidth(rootC->preferredHeight());
	rootC->setPreferredHeight(temp);

	if(content->horizontalAlignment()==HorizontalAlignment::Center)
	{
		content->setHorizontalAlignment(HorizontalAlignment::Left);
		logo->setHorizontalAlignment(HorizontalAlignment::Right);
		logo->setVerticalAlignment(VerticalAlignment::Center);
	}
	else
	{
		content->setHorizontalAlignment(HorizontalAlignment::Center);
		logo->setHorizontalAlignment(HorizontalAlignment::Center);
		logo->setVerticalAlignment(VerticalAlignment::Top);
	}
}

/*void HomeScreen::moveOut()
{
	TranslateTransition *moveOut = TranslateTransition::create(rootC).
			parent(this).
			duration(1000).
			easingCurve(StockCurve::BackOut).
			toX(-768.0f);

	if(OrientationSupport::instance()->orientation()==UIOrientation::Landscape)
	{
		moveOut->setToX(-1280.0f);
	}

	moveOut->play();
}*/
