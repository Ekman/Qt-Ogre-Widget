#ifndef QOGREWIDGET_H
#define	QOGREWIDGET_H

#include <QWidget>
#include <OgreRenderWindow.h>
#include "Game.h"
#include <QMouseEvent>
#include <QPoint>
#include <QPaintEngine>

class QOgreWidget : public QWidget {
	Q_OBJECT
public:
	QOgreWidget(QWidget *parent);
	virtual ~QOgreWidget();

	void createOgreWindow();

	virtual void paintEvent(QPaintEvent* pEvent);
	virtual void resizeEvent(QResizeEvent* rEvent);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual QPaintEngine* paintEngine() const;

	void calculateMouseCenter();
private:
	Ogre::RenderWindow *renderWindow;
	QPoint mouseCenter;

	Ogre::String getWindowHandle() const;
	Ogre::NameValuePairList getRenderOptions() const;
};

#endif	/* QOGREWIDGET_H */

