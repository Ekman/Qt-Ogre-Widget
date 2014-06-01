#include "QOgreWindow.h"

namespace QtOgre {

QOgreWindow::QOgreWindow(WindowEventListener* windowEvents, const usint &width, const usint &height) :
	QMainWindow(),
	ogreWidget(new QOgreWidget(this, windowEvents)),
	actionUpdateTimer(new QTimer(this)),
	windowEvents(windowEvents) {

	setWindowTitle("Window");
	resize(width, height);

	init();
}

QOgreWindow::~QOgreWindow() {
	delete actionUpdateTimer;
	delete ogreWidget;
}

void QOgreWindow::onUpdateActions() {
	windowEvents->onAction(actionUpdateTimer->interval());
}

void QOgreWindow::keyPressEvent(QKeyEvent *event) {
	try {
		const WindowEventListener::_KEY index = mapQtKey(event->key());
		windowEvents->onKeyPressed(index);
	} catch(const std::exception &e) {
		// No mapping for pressed key
	}
}

void QOgreWindow::keyReleaseEvent(QKeyEvent *event) {
	try {
		const WindowEventListener::_KEY index = mapQtKey(event->key());
		windowEvents->onKeyReleased(index);
	} catch(const std::exception &e) {
		// No mapping for pressed key
	}
}

void QOgreWindow::moveEvent(QMoveEvent *event) {
	QWidget::moveEvent(event);
	ogreWidget->calculateMouseCenter();
}

void QOgreWindow::init() {
	ogreWidget->createRenderWindow();
	setCentralWidget(ogreWidget);

	startActionTimer();
}

void QOgreWindow::startActionTimer() const {
	const usint msBetweenActions = (1 / (double) windowEvents->getActionsPerSecond()) * 1000;
	connect(actionUpdateTimer, SIGNAL(timeout()), this, SLOT(onUpdateActions()));
	actionUpdateTimer->start(msBetweenActions);
}

WindowEventListener::_KEY QOgreWindow::mapQtKey(const int &key) {
	switch (key) {
		case Qt::Key_Q:
			return WindowEventListener::KEY_SHUTDOWN;
		case Qt::Key_W:
			return WindowEventListener::KEY_MOVE_FORWARD;
		case Qt::Key_S:
			return WindowEventListener::KEY_MOVE_BACKWARDS;
		case Qt::Key_A:
			return WindowEventListener::KEY_STRAFE_LEFT;
		case Qt::Key_D:
			return WindowEventListener::KEY_STRAFE_RIGHT;
		case Qt::Key_Space:
			return WindowEventListener::KEY_JUMP;
		case Qt::Key_C:
			return WindowEventListener::KEY_ATTACK;
		case Qt::Key_E:
			return WindowEventListener::KEY_USE;
		default:
			throw std::exception();
	}
}

}
