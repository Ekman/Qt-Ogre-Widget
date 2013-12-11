#ifndef QTOGREWINDOW_H
#define	QTOGREWINDOW_H

#include <QMainWindow>
#include "Qt/QOgreWidget.h"
#include "Game.h"
#include <QObject>
#include <QKeyEvent>
#include <QMoveEvent>

class QOgreWindow : public QMainWindow {
	Q_OBJECT
public:
	QOgreWindow();
	virtual ~QOgreWindow();
	virtual void keyPressEvent(QKeyEvent *event);
	virtual void moveEvent(QMoveEvent *event);
private:
	QOgreWidget *ogreWidget;
	Game *game;
	void attachOgreWidget();
};

#endif	/* QTOGREWINDOW_H */

