#ifndef QOGREWINDOW_H
#define QOGREWINDOW_H

#include "PreProcessor.h"
#include "WindowEventListener.h"
#include "QOgreWidget.h"

namespace QtOgre {

class QOgreWidget;

/**
 * @brief Qt window class that creates and hosts a QOgreWidget
 */
class QOgreWindow : public QMainWindow
{
	Q_OBJECT
public slots:
	/**
	 * @brief onUpdateActions Timer callback for when actions should be updated
	 */
	void onUpdateActions();
public:
	/**
	 * @brief QOgreWindow
	 * @param windowEvents Window event callback
	 * @param setupEvent Setup event callback
	 */
	QOgreWindow(WindowEventListener* windowEvents, const usint &width = 800, const usint &height = 600);
	virtual ~QOgreWindow();

	/**
	 * @brief mapQtKey Map a Qt key to the WindowEventListener::KEY enum
	 * @param key Key that has been pressed (QtKey)
	 * @return Correct key to be used in the app
	 */
	static WindowEventListener::_KEY mapQtKey(const int &key);

	// Qt functions
	virtual void keyPressEvent(QKeyEvent *event);
	virtual void keyReleaseEvent(QKeyEvent *event);
	virtual void moveEvent(QMoveEvent *event);
private:
	/**
	 * @brief ogreWidget Contains a reference to the hosted QOgreWidget
	 */
	QOgreWidget* ogreWidget;

	/**
	 * @brief actionUpdateTimer Contains a reference to the timer that should update actions in the game
	 */
	QTimer* actionUpdateTimer;

	/**
	 * @brief windowEvents Window event callback
	 */
	WindowEventListener* windowEvents;

	void init();
	void startActionTimer() const;

	// Disallow to copy the object, Qt::MainWindow doesn't allow it!
	inline QOgreWindow(const QOgreWindow &obj) {
		throw std::runtime_error("Not allowed to copy QOgreWindow");
	}
};

}

#endif // QOGREWINDOW_H
