

#ifndef ApplicationUI_HPP_
#define ApplicationUI_HPP_

#include "Bubble/BubbleGame.h"
#include "GameResult.h"
#include "Screens/HelpPage.h"
#include "Screens/HighScoresPage.h"
#include "Screens/HomeScreen.h"
#include "Screens/InfoPage.h"
#include "Screens/LoadingScreen.h"
#include "Screens/PausePage.h"
//#include "Screens/SettingsPage.h"

//#include <QObject>
/*#include <bb/cascades/AbsoluteLayout>
#include <bb/cascades/AbsoluteLayoutProperties>*/
#include <bb/cascades/Page>
#include <bb/cascades/ScaleTransition>

#include <bb/platform/bbm/Context>
#include <bb/platform/bbm/MessageService>
#include <bb/platform/bbm/UserProfile>

namespace bb
{
namespace cascades
{
class Application;
}
}

using namespace bb::cascades;

class ApplicationUI : public QObject
{
	Q_OBJECT
	signals:
	void resumeGame();
private slots:
	void deleteHelpPage();
	void goBackFromHelp();
	void goToHelpFromHomeScreen();
	void goToHelpFromResult();
	void deleteHighScoresPage();
	void goBackFromHighScores();
	void goToHighScoresFromHomeScreen();
	void deleteInfoPage();
	void goBackFromInfo();
	void goToInfoFromHomeScreen();
	void goToInfoFromResult();
	void deleteSettingsPage();
	void goBackFromSettings();
	//void goToSettings();
	void handleLoadingDone();
	void handleLoadingAnimationEnded();
	void handleMoveDownEnded();
	void handleMoveRightEnded();
	void handleMoveLeftEnded();
	void handleMoveUpEnded();
	void handleOrientationChange();
	void handlePause();
	void handleResume();
	void handleResumeAnimationEnded();
	void handleTimeout(int, int);
	void handleTranslationXChanged(float newVal);
	void handleTranslationYChanged(float newVal);
	//void resetBubbleSet();
	void registrationStateUpdated(bb::platform::bbm::RegistrationState::Type);
	void resetToHomeScreen();
	void shareApp();
	void shareAllHighScores();
	void shareNewHighScore(int);
	void startNewGame();
	void startNewGameFromResult();

public:
	ApplicationUI(Application*);
	~ApplicationUI();

private:
	void resetOrder();
	void resetShapes();

	Container *innerRoot;
	QSettings *highScores;
	TranslateTransition *moveDown, *moveRight, *moveUp, *moveLeft;
	bool fromHomeScreen;

	bb::platform::bbm::UserProfile *m_userProfile;
	bb::platform::bbm::Context *m_context;
	bb::platform::bbm::MessageService *m_messageService;
};

#endif /* ApplicationUI_HPP_ */
