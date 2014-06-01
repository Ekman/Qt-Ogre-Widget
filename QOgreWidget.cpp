#include "QOgreWidget.h"

namespace QtOgre {

QOgreWidget::QOgreWidget(QWidget *parent, WindowEventListener* windowEvent) :
	QWidget(parent),
	windowEvent(windowEvent) {

	this->setAttribute(Qt::WA_OpaquePaintEvent);
	this->setAttribute(Qt::WA_PaintOnScreen);
	this->setMouseTracking(true);
	this->setCursor(QCursor(Qt::BlankCursor));
	this->setFocusPolicy(Qt::StrongFocus);
}

QOgreWidget::~QOgreWidget() {
}

void QOgreWidget::createRenderWindow() {
#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX
	// Weird? It is not working on Linux without it
	this->resize(this->width(), this->height());
#else
	this->resize(this->parentWidget()->width(), this->parentWidget()->height());
#endif

	Ogre::Root *root = Ogre::Root::getSingletonPtr();

	Ogre::NameValuePairList options = this->getRenderOptions();
	renderWindow = root->createRenderWindow("QOgreWidget-RenderWindow",
						parentWidget()->width(),
						parentWidget()->height(),
						false,
						&options);

#if OGRE_DEBUG_MODE == 1
	assert(renderWindow);
#endif

	renderWindow->setActive(true);
	renderWindow->setVisible(true);
	renderWindow->setAutoUpdated(false);

	windowEvent->onSetup(renderWindow);
}

void QOgreWidget::paintEvent(QPaintEvent* event) {
	windowEvent->onGraphics();
	this->update();
}

void QOgreWidget::resizeEvent(QResizeEvent* event) {
	QWidget::resizeEvent(event);

	if (renderWindow != NULL) {
		renderWindow->reposition(x(), y());
		renderWindow->resize(width(), height());
		renderWindow->windowMovedOrResized();
	}

	this->calculateMouseCenter();
}

Ogre::String QOgreWidget::getWindowHandle() const {
	Ogre::String windowHandle;
#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX
	windowHandle = Ogre::StringConverter::toString((unsigned long) QX11Info::display()) + ":";
	windowHandle += Ogre::StringConverter::toString((unsigned int) QX11Info::appScreen()) + ":";
#endif

	windowHandle += Ogre::StringConverter::toString((unsigned long) winId());
	return windowHandle;
}

Ogre::NameValuePairList QOgreWidget::getRenderOptions() const {
	Ogre::NameValuePairList options;

	options["externalWindowHandle"] = getWindowHandle();
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
	options["macAPI"] = "cocoa";
	options["macAPICocoaUseNSView"] = "true";
#endif

	return options;
}

void QOgreWidget::mouseMoveEvent(QMouseEvent *event) {
	const QPoint point = mouseCenter - event->globalPos();
	// Pass the mouse coordinates along to the game
	windowEvent->onMouseMoved(point.x(), point.y());
	// Center mouse
	cursor().setPos(mouseCenter);
}

QPaintEngine* QOgreWidget::paintEngine() const {
	// Make sure Qt isnt painting, we only care about OGREs paint
	return 0;
}

void QOgreWidget::calculateMouseCenter() {
	// Recalculate the center point after the window has been moved or resized
	mouseCenter = mapToGlobal(rect().center());
}

}
