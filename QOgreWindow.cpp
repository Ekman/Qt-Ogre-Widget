#include "Qt/QOgreWindow.h"
#include "Logger.h"
#include "Game.h"

QOgreWindow::QOgreWindow() : ogreWidget(new QOgreWidget(this)), game(&Game::getInstance()) {
	this->attachOgreWidget();
}

QOgreWindow::~QOgreWindow() {
	delete ogreWidget;
}

void QOgreWindow::attachOgreWidget() {
	this->setWindowTitle(Game::WINDOW_TITLE.c_str());
	this->resize(Game::WIDTH, Game::HEIGHT);

	// Create the OGRE rendering window
	ogreWidget->createOgreWindow();

	this->setCentralWidget(ogreWidget);
}

void QOgreWindow::keyPressEvent(QKeyEvent *event) {
	switch (event->key()) {
	case Qt::Key_Q:
		game->captureKeyboard(Game::KEY_SHUTDOWN);
		break;
	case Qt::Key_W:
		game->captureKeyboard(Game::KEY_MOVE_FORWARD);
		break;
	case Qt::Key_S:
		game->captureKeyboard(Game::KEY_MOVE_BACKWARDS);
		break;
	case Qt::Key_A:
		game->captureKeyboard(Game::KEY_STRAFE_LEFT);
		break;
	case Qt::Key_D:
		game->captureKeyboard(Game::KEY_STRAFE_RIGHT);
		break;
	}
}

void QOgreWindow::moveEvent(QMoveEvent *event) {
	QWidget::moveEvent(event);
	ogreWidget->calculateMouseCenter();
}

