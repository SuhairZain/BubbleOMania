/*
 * PausePage.cpp
 *
 *  Created on: Apr 23, 2014
 *      Author: SuhairZain
 */

#include "PausePage.h"

PausePage::PausePage()
{
	ImageView *BG = ImageView::create().
			horizontal(HorizontalAlignment::Fill).
			vertical(VerticalAlignment::Fill).
			image("asset:///images/BG/homeScreenBG.png");

	MovingBG *movingBG = new MovingBG;
	movingBG->setHorizontalAlignment(HorizontalAlignment::Center);
	movingBG->setVerticalAlignment(VerticalAlignment::Top);

	ImageView *grass = ImageView::create().
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Bottom).
			image("asset:///images/tree/grass.png");

	ImageView *board = ImageView::create().
			image("asset:///images/tree/resume.png");

	ImageButton *resumeButton = ImageButton::create().
			layoutProperties(AbsoluteLayoutProperties::create().position(238.0f, 260.0f)).
			defaultImage("asset:///images/tree/resumeButton.png").
			pressedImage("asset:///images/tree/resumeButton.png").
			connect(SIGNAL(clicked()), this, SIGNAL(resume()));

	Container *content = Container::create().
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Bottom).
			layout(AbsoluteLayout::create()).
			add(board).
			add(resumeButton);

	rootC = Container::create().
			layout(DockLayout::create()).
			preferredSize(768.0f, 1280.0f).
			add(BG).
			add(movingBG).
			add(content).
			add(grass);

	if(OrientationSupport::instance()->orientation()==UIOrientation::Landscape)
		rootC->setPreferredSize(1280.0f, 768.0f);

	connect(OrientationSupport::instance(), SIGNAL(orientationAboutToChange(bb::cascades::UIOrientation::Type)), this, SLOT(handleOrientationChange()));

	setRoot(rootC);
}

void PausePage::handleOrientationChange()
{
	float temp = rootC->preferredWidth();
	rootC->setPreferredWidth(rootC->preferredHeight());
	rootC->setPreferredHeight(temp);
}
