/*
 * HighScoresPage.cpp
 *
 *  Created on: Apr 24, 2014
 *      Author: SuhairZain
 */

#include "HighScoresPage.h"

HighScoresPage::HighScoresPage(int first, int second, int third)
{
	ImageView *BG = ImageView::create().
			horizontal(HorizontalAlignment::Fill).
			vertical(VerticalAlignment::Fill).
			image("asset:///images/BG/BG.png");

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

	TextStyle style;
	style.setColor(Color::White);
	style.setFontSize(FontSize::XLarge);

	ImageView *scoreBoardBG = ImageView::create().
			image("asset:///images/highScore/highScore.png");

	Label *firstLabel = Label::create().
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Bottom).
			textStyle(style);
	if(first!=0)
		firstLabel->setText(QString::number(first));

	Container *firstC = Container::create().
			layout(DockLayout::create()).
			layoutProperties(AbsoluteLayoutProperties::create().position(34.0f, 220.0f)).
			preferredSize(632.0f, 50.0f).
			add(firstLabel);

	Label *secondLabel = Label::create().
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Bottom).
			textStyle(style);
	if(second!=0)
		secondLabel->setText(QString::number(second));

	Container *secondC = Container::create().
			layout(DockLayout::create()).
			layoutProperties(AbsoluteLayoutProperties::create().position(34.0f, 299.0f)).
			preferredSize(632.0f, 121.0f).
			add(secondLabel);

	Label *thirdLabel = Label::create().
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Bottom).
			textStyle(style);
	if(third!=0)
		thirdLabel->setText(QString::number(third));

	Container *thirdC = Container::create().
			layout(DockLayout::create()).
			layoutProperties(AbsoluteLayoutProperties::create().position(34.0f, 426.0f)).
			preferredSize(632.0f, 108.0f).
			add(thirdLabel);

	ImageButton *shareAll = ImageButton::create().
			defaultImage("asset:///images/highScore/shareHS.png").
			pressedImage("asset:///images/highScore/shareHS.png").
			layoutProperties(AbsoluteLayoutProperties::create().position(9.0f, 659.0f)).
			connect(SIGNAL(clicked()), this, SIGNAL(shareAllHighScores()));

	Container *content = Container::create().
			layout(AbsoluteLayout::create()).
			horizontal(HorizontalAlignment::Center).
			vertical(VerticalAlignment::Center).
			add(scoreBoardBG).
			add(firstC).
			add(secondC).
			add(thirdC).
			add(shareAll);

	rootC = Container::create().
			layout(DockLayout::create()).
			preferredSize(768.0f, 1280.0f).
			add(BG).
			add(backButtonC).
			add(content);

	if(OrientationSupport::instance()->orientation()==UIOrientation::Landscape)
		rootC->setPreferredSize(1280.0f, 768.0f);

	connect(OrientationSupport::instance(), SIGNAL(orientationAboutToChange(bb::cascades::UIOrientation::Type)), this, SLOT(handleOrientationChange()));

	setRoot(rootC);
}

void HighScoresPage::handleOrientationChange()
{
	float temp = rootC->preferredWidth();
	rootC->setPreferredWidth(rootC->preferredHeight());
	rootC->setPreferredHeight(temp);
}
