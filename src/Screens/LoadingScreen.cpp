/*
 * LoadingScreen.cpp
 *
 *  Created on: Apr 12, 2014
 *      Author: SuhairZain
 */

#include "LoadingScreen.h"

LoadingScreen::LoadingScreen()
{
	OrientationSupport::instance()->setSupportedDisplayOrientation(SupportedDisplayOrientation::CurrentLocked);

	ImageView *BG = ImageView::create().
			image("asset:///images/BG/splash.png");

	Container *expC = Container::create().
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Center).
			background(Color::Blue).
			tx(-768.0f).
			preferredSize(768.0f, 30.0f);

	Container *content = Container::create().
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Bottom).
			layout(DockLayout::create()).
			preferredSize(768.0f, 30.0f).
			add(expC);

	Container *rootC = Container::create().
			layout(DockLayout::create()).
			preferredSize(768.0f, 1280.0f).
			add(BG).
			add(content);

	TranslateTransition *expand = TranslateTransition::create(expC).
			parent(this).
			autoDeleted(TRUE).
			duration(2000).
			easingCurve(StockCurve::CircularIn).
			toX(0.0f).
			connect(SIGNAL(ended()), this, SLOT(animationFinished()));
	expand->play();

	if(OrientationSupport::instance()->orientation()==UIOrientation::Landscape)
	{
		BG->setImage("asset:///images/BG/splashLandscape.png");
		rootC->setPreferredSize(1280.0f, 768.0f);
		expC->setTranslationX(-1280.0f);
		expC->setPreferredWidth(1280.0f);
		content->setPreferredWidth(1280.0f);
	}

	setRoot(rootC);
}

void LoadingScreen::animationFinished()
{
	OrientationSupport::instance()->setSupportedDisplayOrientation(SupportedDisplayOrientation::All);
	emit loadingDone();
}
