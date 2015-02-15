/*
 * Copyright (c) 2011-2013 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "applicationui.hpp"
#include <time.h>

#include <bb/cascades/Application>

ApplicationUI::ApplicationUI(Application *app)
{
	qDebug()<<QDir(QDir::root().absoluteFilePath("app/native/assets/savedShapes.json")).exists();

	highScores = new QSettings("Suhair Zain", "BubbleOMania", this);

	m_context = new bb::platform::bbm::Context(QUuid("a5fee7b3-c445-4d9f-9b92-d039febf3ea2"));
	m_userProfile = NULL;
	m_messageService = NULL;

	fromHomeScreen = FALSE;
	/*BubbleGame *bubbleGame = new BubbleGame;
	connect(bubbleGame, SIGNAL(timeout(int, int)), this, SLOT(handleTimeout(int,int)));

	rootC = Container::create().
			layout(DockLayout::create()).
			add(bubbleGame);*/

	HomeScreen *homeScreen = new HomeScreen;
	homeScreen->setObjectName("homeScreen");
	homeScreen->setLayoutProperties(AbsoluteLayoutProperties::create().position(0.0f, 0.0f));
	connect(homeScreen, SIGNAL(startNewGame()), this, SLOT(startNewGame()));
	connect(homeScreen, SIGNAL(goToHelp()), this, SLOT(goToHelpFromHomeScreen()));
	connect(homeScreen, SIGNAL(goToHighScores()), this, SLOT(goToHighScoresFromHomeScreen()));
	connect(homeScreen, SIGNAL(goToInfo()), this, SLOT(goToInfoFromHomeScreen()));
	//connect(homeScreen, SIGNAL(goToSettings()), this, SLOT(goToSettings()));

	LoadingScreen *loadingScreen = new LoadingScreen;
	loadingScreen->setObjectName("loadingScreen");
	loadingScreen->setLayoutProperties(AbsoluteLayoutProperties::create().position(0.0f, 0.0f));
	connect(loadingScreen, SIGNAL(loadingDone()), this, SLOT(handleLoadingDone()));

	innerRoot = Container::create().
			horizontal(HorizontalAlignment::Left).
			vertical(VerticalAlignment::Top).
			layout(AbsoluteLayout::create()).
			add(homeScreen).
			add(loadingScreen);
	innerRoot->setMinHeight(1280.0f*2);
	innerRoot->setMinWidth(768.0f*2);
	//connect(innerRoot, SIGNAL(translationXChanged(float)), this, SLOT(handleTranslationXChanged(float)));
	//connect(innerRoot, SIGNAL(translationYChanged(float)), this, SLOT(handleTranslationYChanged(float)));

	if(OrientationSupport::instance()->orientation()==UIOrientation::Landscape)
	{
		float temp = innerRoot->minHeight();
		innerRoot->setMinHeight(innerRoot->minWidth());
		innerRoot->setMinWidth(temp);
	}

	Container *rootC = Container::create().
			layout(DockLayout::create()).
			add(innerRoot);

	Page *root = Page::create().
			content(rootC);

	/*navPane = NavigationPane::create().
			add(root).
			backButtons(FALSE).
			peek(FALSE);*/

	app->setMenuEnabled(FALSE);
	app->setScene(root);


	moveDown = TranslateTransition::create(innerRoot).
			parent(this).
			duration(500).
			toY(-1280.0f).
			connect(SIGNAL(ended()), this, SLOT(handleMoveDownEnded()));

	moveRight = TranslateTransition::create(innerRoot).
			parent(this).
			duration(500).
			toX(-768.0f).
			connect(SIGNAL(ended()), this, SLOT(handleMoveRightEnded()));

	moveLeft = TranslateTransition::create(innerRoot).
			parent(this).
			duration(500).
			toX(0.0f).
			connect(SIGNAL(ended()), this, SLOT(handleMoveLeftEnded()));

	moveUp = TranslateTransition::create(innerRoot).
			parent(this).
			duration(500).
			toY(0.0f).
			connect(SIGNAL(ended()), this, SLOT(handleMoveUpEnded()));

	connect(OrientationSupport::instance(), SIGNAL(orientationAboutToChange(bb::cascades::UIOrientation::Type)), this, SLOT(handleOrientationChange()));
}

ApplicationUI::~ApplicationUI()
{
	delete m_context;
}

void ApplicationUI::deleteHelpPage()
{
	Control *temp = innerRoot->findChild<Control*>("helpPage");

	innerRoot->remove(temp);
	temp->setParent(0);
	temp->deleteLater();
}

void ApplicationUI::goBackFromHelp()
{
	TranslateTransition *goBack = TranslateTransition::create(innerRoot).
			parent(this).
			autoDeleted(TRUE).
			duration(500).
			connect(SIGNAL(ended()), this, SLOT(deleteHelpPage()));

	if(fromHomeScreen)
		goBack->setToX(0.0f);
	else
		goBack->setToY(-1280.0f);
	if(OrientationSupport::instance()->orientation()==UIOrientation::Landscape)
	{
		if(!fromHomeScreen)
			goBack->setToY(-768.0f);
	}
	goBack->play();
}

void ApplicationUI::goToHelpFromHomeScreen()
{
	fromHomeScreen = TRUE;

	HelpPage *helpPage = new HelpPage;
	helpPage->setObjectName("helpPage");
	float x=768.0f;
	if(OrientationSupport::instance()->orientation()==UIOrientation::Landscape)
	{
		x=1280.0f;
	}
	helpPage->setLayoutProperties(AbsoluteLayoutProperties::create().position(x, 0.0f));
	connect(helpPage, SIGNAL(goBack()), this, SLOT(goBackFromHelp()));

	innerRoot->add(helpPage);

	TranslateTransition *moveR = TranslateTransition::create(innerRoot).
			parent(this).
			autoDeleted(TRUE).
			duration(500).
			toX(-x);
	moveR->play();
}

void ApplicationUI::goToHelpFromResult()
{
	fromHomeScreen = FALSE;

	HelpPage *helpPage = new HelpPage;
	helpPage->setObjectName("helpPage");
	float x=768.0f;
	if(OrientationSupport::instance()->orientation()==UIOrientation::Landscape)
		x=1280.0f;
	helpPage->setLayoutProperties(AbsoluteLayoutProperties::create().position(x, 0.0f));
	connect(helpPage, SIGNAL(goBack()), this, SLOT(goBackFromHelp()));

	innerRoot->add(helpPage);

	TranslateTransition *moveU = TranslateTransition::create(innerRoot).
			parent(this).
			autoDeleted(TRUE).
			duration(500).
			toY(0.0f);
	moveU->play();
}

void ApplicationUI::deleteHighScoresPage()
{
	Control *temp = innerRoot->findChild<Control*>("highScoresPage");

	innerRoot->remove(temp);
	temp->setParent(0);
	temp->deleteLater();
}

void ApplicationUI::goBackFromHighScores()
{
	TranslateTransition *goBack = TranslateTransition::create(innerRoot).
			parent(this).
			autoDeleted(TRUE).
			duration(500).
			connect(SIGNAL(ended()), this, SLOT(deleteHighScoresPage()));

	if(fromHomeScreen)
		goBack->setToX(0.0f);
	else
		goBack->setToY(-1280.0f);
	if(OrientationSupport::instance()->orientation()==UIOrientation::Landscape)
	{
		if(!fromHomeScreen)
			goBack->setToY(-768.0f);
	}
	goBack->play();
}

void ApplicationUI::goToHighScoresFromHomeScreen()
{
	fromHomeScreen = TRUE;

	int first, second, third;
	first = highScores->value("first", 0).toInt();
	second = highScores->value("second", 0).toInt();
	third = highScores->value("third", 0).toInt();

	HighScoresPage *highScoresPage = new HighScoresPage(first, second, third);
	highScoresPage->setObjectName("highScoresPage");
	float x=768.0f;
	if(OrientationSupport::instance()->orientation()==UIOrientation::Landscape)
	{
		x=1280.0f;
	}
	highScoresPage->setLayoutProperties(AbsoluteLayoutProperties::create().position(x, 0.0f));
	connect(highScoresPage, SIGNAL(goBack()), this, SLOT(goBackFromHighScores()));
	connect(highScoresPage, SIGNAL(shareAllHighScores()), this, SLOT(shareAllHighScores()));

	innerRoot->add(highScoresPage);

	TranslateTransition *moveR = TranslateTransition::create(innerRoot).
			parent(this).
			autoDeleted(TRUE).
			duration(500).
			toX(-x);
	moveR->play();
}

void ApplicationUI::deleteInfoPage()
{
	Control *temp = innerRoot->findChild<Control*>("infoPage");

	innerRoot->remove(temp);
	temp->setParent(0);
	temp->deleteLater();
}

void ApplicationUI::goBackFromInfo()
{
	TranslateTransition *goBack = TranslateTransition::create(innerRoot).
			parent(this).
			autoDeleted(TRUE).
			duration(500).
			connect(SIGNAL(ended()), this, SLOT(deleteInfoPage()));

	if(fromHomeScreen)
		goBack->setToX(0.0f);
	else
		goBack->setToY(-1280.0f);
	if(OrientationSupport::instance()->orientation()==UIOrientation::Landscape)
	{
		if(!fromHomeScreen)
			goBack->setToY(-768.0f);
	}
	goBack->play();
}

void ApplicationUI::goToInfoFromHomeScreen()
{
	fromHomeScreen = TRUE;

	InfoPage *infoPage = new InfoPage;
	infoPage->setObjectName("infoPage");
	float x=768.0f;
	if(OrientationSupport::instance()->orientation()==UIOrientation::Landscape)
		x=1280.0f;
	infoPage->setLayoutProperties(AbsoluteLayoutProperties::create().position(x, 0.0f));
	connect(infoPage, SIGNAL(goBack()), this, SLOT(goBackFromInfo()));
	//connect(helpPage, SIGNAL(goToHome()), this, SLOT(resetToHomeScreen()));

	innerRoot->add(infoPage);

	TranslateTransition *moveR = TranslateTransition::create(innerRoot).
			parent(this).
			autoDeleted(TRUE).
			duration(500).
			toX(-x);
	moveR->play();
}

void ApplicationUI::goToInfoFromResult()
{
	fromHomeScreen = FALSE;

	InfoPage *infoPage = new InfoPage;
	infoPage->setObjectName("infoPage");
	float x=768.0f;
	if(OrientationSupport::instance()->orientation()==UIOrientation::Landscape)
		x=1280.0f;
	infoPage->setLayoutProperties(AbsoluteLayoutProperties::create().position(x, 0.0f));
	connect(infoPage, SIGNAL(goBack()), this, SLOT(goBackFromInfo()));
	//connect(helpPage, SIGNAL(goToHome()), this, SLOT(resetToHomeScreen()));

	innerRoot->add(infoPage);

	TranslateTransition *moveU = TranslateTransition::create(innerRoot).
			parent(this).
			autoDeleted(TRUE).
			duration(500).
			toY(0.0f);
	moveU->play();
}
void ApplicationUI::deleteSettingsPage()
{
	Control *temp = innerRoot->findChild<Control*>("settingsPage");

	innerRoot->remove(temp);
	temp->setParent(0);
	temp->deleteLater();
}

void ApplicationUI::goBackFromSettings()
{
	TranslateTransition *goBack = TranslateTransition::create(innerRoot).
			parent(this).
			autoDeleted(TRUE).
			duration(500).
			toX(0.0f).
			connect(SIGNAL(ended()), this, SLOT(deleteSettingsPage()));

	goBack->play();
}

/*void ApplicationUI::goToSettings()
{
	fromHomeScreen = TRUE;

	SettingsPage *settingsPage = new SettingsPage;
	settingsPage->setObjectName("settingsPage");
	float x=768.0f;
	if(OrientationSupport::instance()->orientation()==UIOrientation::Landscape)
		x=1280.0f;
	settingsPage->setLayoutProperties(AbsoluteLayoutProperties::create().position(x, 0.0f));
	connect(settingsPage, SIGNAL(goBack()), this, SLOT(goBackFromSettings()));
	//connect(helpPage, SIGNAL(goToHome()), this, SLOT(resetToHomeScreen()));

	innerRoot->add(settingsPage);

	TranslateTransition *moveR = TranslateTransition::create(innerRoot).
			parent(this).
			autoDeleted(TRUE).
			duration(500).
			toX(-x);
	moveR->play();
}*/

void ApplicationUI::handleLoadingDone()
{
	Control *temp = innerRoot->findChild<Control*>("loadingScreen");

	ScaleTransition *loadingAnimation = ScaleTransition::create(temp).
			parent(this).
			autoDeleted(TRUE).
			duration(500).
			easingCurve(StockCurve::BackIn).
			toScale(0.0f).
			connect(SIGNAL(ended()), this, SLOT(handleLoadingAnimationEnded()));
	loadingAnimation->play();
}

void ApplicationUI::handleLoadingAnimationEnded()
{
	Control *temp = innerRoot->findChild<Control*>("loadingScreen");

	innerRoot->remove(temp);
	temp->setParent(0);
	temp->deleteLater();

	if(m_context->registrationState() != bb::platform::bbm::RegistrationState::Allowed)
	{
		connect(m_context, SIGNAL(registrationStateUpdated (bb::platform::bbm::RegistrationState::Type)), this, SLOT(registrationStateUpdated (bb::platform::bbm::RegistrationState::Type)));
		m_context->requestRegisterApplication();
	}

	if(highScores->value("firstTime", TRUE).toBool())
	{
		highScores->setValue("firstTime", FALSE);
		goToHelpFromHomeScreen();
	}
}

void ApplicationUI::handleMoveDownEnded()
{
	qDebug()<<"Down ended";

	Control *temp = innerRoot->findChild<Control*>("homeScreen");

	innerRoot->remove(temp);
	temp->setParent(0);
	temp->deleteLater();

	//QTimer::singleShot(1000, temp, SLOT(deleteLater()));
}

void ApplicationUI::handleMoveRightEnded()
{
	qDebug()<<"Right ended";

	Control *temp = innerRoot->findChild<Control*>("bubbleGame");

	innerRoot->remove(temp);
	temp->setParent(0);
	temp->deleteLater();

	//QTimer::singleShot(1000, temp, SLOT(deleteLater()));
}

void ApplicationUI::handleMoveLeftEnded()
{
	qDebug()<<"Left ended";

	Control *temp = innerRoot->findChild<Control*>("gameResult");

	innerRoot->remove(temp);
	temp->setParent(0);
	temp->deleteLater();
}

void ApplicationUI::handleMoveUpEnded()
{
	qDebug()<<"Up ended";

	TranslateTransition *tempAnimation = TranslateTransition::create(innerRoot).
			parent(this).
			autoDeleted(TRUE).
			duration(0).
			toX(0.0f);
	tempAnimation->play();

	Control *temp = innerRoot->findChild<Control*>("gameResult");

	innerRoot->remove(temp);
	temp->setParent(0);
	temp->deleteLater();

	temp = innerRoot->findChild<Control*>("homeScreen2");

	innerRoot->remove(temp);
	temp->setParent(0);
	temp->deleteLater();
}

void ApplicationUI::handleOrientationChange()
{
	float temp = innerRoot->minWidth();
	innerRoot->setMinWidth(innerRoot->minHeight());
	innerRoot->setMinHeight(temp);

	float currTX = innerRoot->translationX();
	/*if(currTX==768.0f)
		innerRoot->setTranslationX(1280.0f);
	else if(currTX==1280.0f)
		innerRoot->setTranslationX(768.0f);
	else */
	if(currTX==-768.0f)
		innerRoot->setTranslationX(-1280.0f);
	else if(currTX==-1280.0f)
		innerRoot->setTranslationX(-768.0f);

	float currTY = innerRoot->translationY();
	/*if(currTY==768.0f)
		innerRoot->setTranslationY(1280.0f);
	else if(currTY==1280.0f)
		innerRoot->setTranslationY(768.0f);
	else */
	if(currTY==-768.0f)
		innerRoot->setTranslationY(-1280.0f);
	else if(currTY==-1280.0f)
		innerRoot->setTranslationY(-768.0f);

	AbsoluteLayoutProperties *layout;
	float currX, currY;

	for(int i=0; i<innerRoot->count(); i++)
	{
		layout = static_cast<AbsoluteLayoutProperties*>(innerRoot->at(i)->layoutProperties());

		currX = layout->positionX();
		if(currX==768.0f)
			layout->setPositionX(1280.0f);
		else if(currX==1280.0f)
			layout->setPositionX(768.0f);

		currY = layout->positionY();
		if(currY==768.0f)
			layout->setPositionY(1280.0f);
		else if(currY==1280.0f)
			layout->setPositionY(768.0f);
	}
}

void ApplicationUI::handlePause()
{
	PausePage *pausePage = new PausePage;
	pausePage->setObjectName("pausePage");
	pausePage->setLayoutProperties(AbsoluteLayoutProperties::create().position(0.0f, 0.0f));
	connect(pausePage, SIGNAL(resume()), this, SLOT(handleResume()));

	innerRoot->add(pausePage);

	TranslateTransition *moveU = TranslateTransition::create(innerRoot).
			parent(this).
			autoDeleted(TRUE).
			duration(1000).
			easingCurve(StockCurve::DoubleBounceOut).
			toY(0.0f);
	moveU->play();
}

void ApplicationUI::handleResume()
{
	TranslateTransition *goBack = TranslateTransition::create(innerRoot).
			parent(this).
			autoDeleted(TRUE).
			duration(500).
			toY(-1280.0f).
			connect(SIGNAL(ended()), this, SLOT(handleResumeAnimationEnded()));

	if(OrientationSupport::instance()->orientation()==UIOrientation::Landscape)
		goBack->setToY(-768.0f);
	goBack->play();
}

void ApplicationUI::handleResumeAnimationEnded()
{
	emit resumeGame();

	Control *temp = innerRoot->findChild<Control*>("pausePage");

	innerRoot->remove(temp);
	temp->setParent(0);
	temp->deleteLater();
}

void ApplicationUI::handleTimeout(int nISOTB, int level)
{
	int placeSecured;
	int first, second, third, totalScore;
	first = highScores->value("first", 0).toInt();
	second = highScores->value("second", 0).toInt();
	third = highScores->value("third", 0).toInt();
	totalScore = (level-1)*100 + nISOTB*50;
	if(totalScore>first)
	{
		placeSecured = 1;
		highScores->setValue("third", second);
		highScores->setValue("second", first);
		highScores->setValue("first", totalScore);
	}
	else if(totalScore>second)
	{
		placeSecured = 2;
		highScores->setValue("third", second);
		highScores->setValue("second", totalScore);
	}
	else if(totalScore>third)
	{
		placeSecured = 3;
		highScores->setValue("third", totalScore);
	}
	else
		placeSecured = 0;
	highScores->sync();

	GameResult *result = new GameResult(nISOTB, level, placeSecured);
	result->setObjectName("gameResult");
	float x=768.0f, y=1280.0f;
	if(OrientationSupport::instance()->orientation()==UIOrientation::Landscape)
	{
		x=1280.0f;
		y=768.0f;
	}
	result->setLayoutProperties(AbsoluteLayoutProperties::create().position(x, y));
	connect(result, SIGNAL(goToNextGame()), this, SLOT(startNewGameFromResult()));
	connect(result, SIGNAL(goToHome()), this, SLOT(resetToHomeScreen()));
	connect(result, SIGNAL(shareHS(int)), this, SLOT(shareNewHighScore(int)));

	innerRoot->add(result);

	if(OrientationSupport::instance()->orientation()==UIOrientation::Landscape)
		moveRight->setToX(-1280.0f);
	else
		moveRight->setToX(-768.0f);

	moveRight->play();
}

void ApplicationUI::handleTranslationXChanged(float newVal)
{
	qDebug()<<"X:"<<newVal;
}

void ApplicationUI::handleTranslationYChanged(float newVal)
{
	qDebug()<<"Y:"<<newVal;
}
/*
void ApplicationUI::resetBubbleSet()
{
	BubbleGame *bubbleGame = new BubbleGame;
	bubbleGame->setObjectName("bubbleGame");
	connect(bubbleGame, SIGNAL(timeout(int, int)), this, SLOT(handleTimeout(int,int)));

	Control *temp = innerRoot->findChild<Control*>("bubbleGame");
	int index = innerRoot->indexOf(temp);
	innerRoot->replace(index, bubbleGame);
	temp->setParent(0);

	QTimer::singleShot(1000, temp, SLOT(deleteLater()));
}*/

void ApplicationUI::registrationStateUpdated(bb::platform::bbm::RegistrationState::Type state)
{
	if(state==bb::platform::bbm::RegistrationState::Allowed)
	{
		m_messageService = new bb::platform::bbm::MessageService(m_context, this);
		m_userProfile = new bb::platform::bbm::UserProfile(m_context, this);
	}
	else if(state == bb::platform::bbm::RegistrationState::Unregistered)
	{
	    qDebug()<<"H";
		m_context->requestRegisterApplication();
	}
}

void ApplicationUI::resetToHomeScreen()
{
	HomeScreen *homeScreen2 = new HomeScreen;
	homeScreen2->setObjectName("homeScreen2");

	float x=768.0f;
	if(OrientationSupport::instance()->orientation()==UIOrientation::Landscape)
		x=1280.0f;
	homeScreen2->setLayoutProperties(AbsoluteLayoutProperties::create().position(x, 0.0f));


	innerRoot->add(homeScreen2);

	HomeScreen *homeScreen = new HomeScreen;
	homeScreen->setObjectName("homeScreen");
	homeScreen->setLayoutProperties(AbsoluteLayoutProperties::create().position(0.0f, 0.0f));
	connect(homeScreen, SIGNAL(startNewGame()), this, SLOT(startNewGame()));
	connect(homeScreen, SIGNAL(goToHelp()), this, SLOT(goToHelpFromHomeScreen()));
	connect(homeScreen, SIGNAL(goToHighScores()), this, SLOT(goToHighScoresFromHomeScreen()));
	connect(homeScreen, SIGNAL(goToInfo()), this, SLOT(goToInfoFromHomeScreen()));
	//connect(homeScreen, SIGNAL(goToSettings()), this, SLOT(goToSettings()));

	innerRoot->add(homeScreen);

	/*if(OrientationSupport::instance()->orientation()==UIOrientation::Landscape)
		moveUp->setToX(-1280.0f);
	else
		moveUp->setToX(-768.0f);*/

	moveUp->play();
}

void ApplicationUI::shareApp()
{
	if(m_context->registrationState() == bb::platform::bbm::RegistrationState::Allowed)
	{
		m_messageService->sendDownloadInvitation();
	}
	else
	{
		/*	toast->setBody("BBM is not currently connected. Please setup/sign-in to BBM.");
		toast->setIcon(QUrl("asset:///images/icons/ic_bbm.png"));
		toast->show();*/
		m_context->requestRegisterApplication();
	}
}

void ApplicationUI::shareAllHighScores()
{
	if (m_context->registrationState() == bb::platform::bbm::RegistrationState::Allowed)
	{
	    qDebug()<<"Allowed";
		int first, second, third;
		first = highScores->value("first", 0).toInt();
		second = highScores->value("second", 0).toInt();
		third = highScores->value("third", 0).toInt();

		QString statusMessage;
		if(first!=0 && second!=0 && third!=0)
			statusMessage = "Yeah! My scores in Bubble O' Mania: " + QString::number(first) + ", " + QString::number(second) + " and " + QString::number(third);
		else if(first!=0 && second!=0)
			statusMessage = "Yeah! My scores in Bubble O' Mania are " + QString::number(first) + " and " + QString::number(second);
		else if(first!=0)
			statusMessage = "Yeah! My score in Bubble O' Mania is " + QString::number(first);
		else
			statusMessage = "I'm playing Bubble O' Mania. Haven't you downloaded it yet?";

		m_userProfile->requestUpdatePersonalMessage(statusMessage);
	}
	else
	{
		/*toast->setBody("BBM is not currently connected. Please setup/sign-in to BBM.");
		toast->setIcon(QUrl("asset:///images/icons/ic_bbm.png"));
		toast->show();*/
	    qDebug()<<"Sharing all";
		m_context->requestRegisterApplication();
	}
}

void ApplicationUI::shareNewHighScore(int newScore)
{
	if (m_context->registrationState() == bb::platform::bbm::RegistrationState::Allowed)
	{
		QString statusMessage;
		statusMessage = "Yeah! I've got a score of " + QString::number(newScore) + " in Bubble O' Mania";

		m_userProfile->requestUpdatePersonalMessage(statusMessage);
	}
	else
	{
		/*toast->setBody("BBM is not currently connected. Please setup/sign-in to BBM.");
		toast->setIcon(QUrl("asset:///images/icons/ic_bbm.png"));
		toast->show();*/
		m_context->requestRegisterApplication();
	}
}

void ApplicationUI::startNewGame()
{
	BubbleGame *bubbleGame = new BubbleGame;
	bubbleGame->setObjectName("bubbleGame");
	float y=1280.0f;
	if(OrientationSupport::instance()->orientation()==UIOrientation::Landscape)
		y=768.0f;
	bubbleGame->setLayoutProperties(AbsoluteLayoutProperties::create().position(0.0f, y));
	connect(bubbleGame, SIGNAL(pauseGame()), this, SLOT(handlePause()));
	connect(bubbleGame, SIGNAL(timeout(int, int)), this, SLOT(handleTimeout(int,int)));
	connect(this, SIGNAL(resumeGame()), bubbleGame, SIGNAL(resumeGame()));

	innerRoot->add(bubbleGame);

	if(OrientationSupport::instance()->orientation()==UIOrientation::Landscape)
		moveDown->setToY(-768.0f);
	else
		moveDown->setToY(-1280.0f);

	moveDown->play();
	//QTimer::singleShot(1000, temp, SLOT(deleteLater()));
}

void ApplicationUI::startNewGameFromResult()
{
	BubbleGame *bubbleGame = new BubbleGame;
	bubbleGame->setObjectName("bubbleGame");
	float y=1280.0f;
	if(OrientationSupport::instance()->orientation()==UIOrientation::Landscape)
		y=768.0f;
	bubbleGame->setLayoutProperties(AbsoluteLayoutProperties::create().position(0.0f, y));
	connect(bubbleGame, SIGNAL(pauseGame()), this, SLOT(handlePause()));
	connect(bubbleGame, SIGNAL(timeout(int, int)), this, SLOT(handleTimeout(int,int)));
	connect(this, SIGNAL(resumeGame()), bubbleGame, SIGNAL(resumeGame()));

	innerRoot->add(bubbleGame);

	/*if(OrientationSupport::instance()->orientation()==UIOrientation::Landscape)
		moveRight->setToX(-1280.0f);
	else
		moveRight->setToX(-768.0f);*/

	moveLeft->play();
}
