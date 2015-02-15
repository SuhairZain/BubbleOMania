/*
 * InfoPage.cpp
 *
 *  Created on: Apr 12, 2014
 *      Author: SuhairZain
 */

#include "InfoPage.h"

InfoPage::InfoPage()
{
	ImageView *BG = ImageView::create().
			//horizontal(HorizontalAlignment::Fill).
			//vertical(VerticalAlignment::Fill).
			image("asset:///images/BG/aboutBG.png");

	ImageButton *backButton = ImageButton::create().
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Center).
			defaultImage("asset:///images/icons/back.png").
			pressedImage("asset:///images/icons/backPressed.png").
			connect(SIGNAL(clicked()), this, SIGNAL(goBack()));

	Container *backButtonC = Container::create().
			horizontal(HorizontalAlignment::Left).
			vertical(VerticalAlignment::Top).
			layout(DockLayout::create()).
			add(backButton).
			top(20.0f).
			left(20.0f);

	Container *content = Container::create().
			horizontal(HorizontalAlignment::Fill).
			vertical(VerticalAlignment::Fill);

	rootC = Container::create().
	        horizontal(HorizontalAlignment::Fill).
	        vertical(VerticalAlignment::Fill).
			layout(DockLayout::create()).
			preferredSize(768.0f, 1280.0f).
			add(BG).
			add(content).
            add(backButtonC);

	if(OrientationSupport::instance()->orientation()==UIOrientation::Landscape)
		rootC->setPreferredSize(1280.0f, 768.0f);

	connect(OrientationSupport::instance(), SIGNAL(orientationAboutToChange(bb::cascades::UIOrientation::Type)), this, SLOT(handleOrientationChange()));

	setRoot(rootC);
}

void InfoPage::handleOrientationChange()
{
	float temp = rootC->preferredWidth();
	rootC->setPreferredWidth(rootC->preferredHeight());
	rootC->setPreferredHeight(temp);
}
