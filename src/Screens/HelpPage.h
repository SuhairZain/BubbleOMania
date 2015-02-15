/*
 * HelpPage.h
 *
 *  Created on: Apr 12, 2014
 *      Author: SuhairZain
 */

#ifndef HELPPAGE_H_
#define HELPPAGE_H_

#include <bb/cascades/Container>
#include <bb/cascades/CustomControl>
#include <bb/cascades/DockLayout>
#include <bb/cascades/ImageButton>
#include <bb/cascades/ImageView>
#include <bb/cascades/OrientationSupport>

using namespace bb::cascades;

class HelpPage: public CustomControl
{
	Q_OBJECT
signals:
	void goBack();
private slots:
	void handleOrientationChange();
public:
	HelpPage();
private:
	Container *rootC;
};

#endif /* HELPPAGE_H_ */
