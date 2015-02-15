/*
 * InfoPage.h
 *
 *  Created on: Apr 12, 2014
 *      Author: SuhairZain
 */

#ifndef INFOPAGE_H_
#define INFOPAGE_H_

#include <bb/cascades/Container>
#include <bb/cascades/CustomControl>
#include <bb/cascades/DockLayout>
#include <bb/cascades/ImageButton>
#include <bb/cascades/ImageView>
#include <bb/cascades/OrientationSupport>

using namespace bb::cascades;

class InfoPage: public CustomControl
{
	Q_OBJECT
signals:
	void goBack();
private slots:
	void handleOrientationChange();
public:
	InfoPage();
private:
	Container *rootC;
};

#endif /* INFOPAGE_H_ */
