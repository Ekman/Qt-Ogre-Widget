#include "Qt/QOgreWidget.h"
#include "Logger.h"
#include <OgreRoot.h>
#include <QRect>

#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX
#include <QX11Info>
#endif

QOgreWidget::QOgreWidget(QWidget *parent) : QWidget(parent) {
}

QOgreWidget::~QOgreWidget() {
}

void QOgreWidget::createOgreWindow() {
#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX
	// Weird? It is not working on Linux without it
	this->resize(this->width(), this->height());
#else
	this->resize(this->parentWidget()->width(), this->parentWidget()->height());
#endif

	this->setAttribute(Qt::WA_OpaquePaintEvent);
	this->setAttribute(Qt::WA_PaintOnScreen);

	Ogre::Root *root = Ogre::Root::getSingletonPtr();

	Ogre::NameValuePairList options = this->getRenderOptions();
	renderWindow = root->createRenderWindow("QOgreWidget-RenderWindow", width(), height(), false, &options);
	renderWindow->setActive(true);
	
	// Perhaps do something with the rendering window?
	// I pass it along to another class that handles the updates

	this->setMouseTracking(true);
#if OGRE_PLATFORM != OGRE_PLATFORM_APPLE
	// Doesnt work on mac, so dont compile it
	this->setCursor(QCursor(Qt::BlankCursor));
#endif
}

void QOgreWidget::paintEvent(QPaintEvent* event) {
	// I call another class that handles frame rendering etc
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

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
	windowHandle = Ogre::StringConverter::toString((unsigned long) this->winId());
#elif OGRE_PLATFORM == OGRE_PLATFORM_LINUX
	windowHandle = Ogre::StringConverter::toString((unsigned long) QX11Info::display()) + ":";
	windowHandle += Ogre::StringConverter::toString((unsigned int) QX11Info::appScreen()) + ":";
	windowHandle += Ogre::StringConverter::toString((unsigned long) this->winId());
#else
	windowHandle = Ogre::StringConverter::toString((unsigned long) this->parentWidget()->winId());
#endif

	return windowHandle;
}

Ogre::NameValuePairList QOgreWidget::getRenderOptions() const {
	Ogre::String windowHandle = this->getWindowHandle();

	Ogre::NameValuePairList options;

	options["externalWindowHandle"] = windowHandle;
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
	options["macAPI"] = "cocoa";
	options["macAPICocoaUseNSView"] = "true";
#endif

	return options;
}

void QOgreWidget::mouseMoveEvent(QMouseEvent *event) {
	const QPoint point = event->globalPos() - mouseCenter;

	double x = point.x();
	double y = point.y();

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
	// Sensitivity on mac is crazy! These should be replaced with a mouse
	// sensitivity setting in the future.
	x /= 2;
	y /= 2;
#endif

	// Pass the mouse coordinates along to another class

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
