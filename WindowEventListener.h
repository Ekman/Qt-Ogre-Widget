#ifndef QT_OGRE_EVENTLISTENER_H
#define QT_OGRE_EVENTLISTENER_H

#include "PreProcessor.h"

namespace QtOgre {

/**
 * @brief Event callback listener for window events
 */
class WindowEventListener
{
public:
	/**
	 * @brief Contains own implementation of keys
	 */
	enum _KEY {
		KEY_SHUTDOWN,
		KEY_MOVE_FORWARD,
		KEY_MOVE_BACKWARDS,
		KEY_STRAFE_LEFT,
		KEY_STRAFE_RIGHT,
		KEY_JUMP,
		KEY_ATTACK,
		KEY_USE,
		KEY_COUNT
	};

	/**
	 * @brief EventListener
	 * @param actionsPerSecond Actions per second
	 */
	inline WindowEventListener(const usint& actionsPerSecond) :
		actionsPerSecond(actionsPerSecond) {
#if OGRE_DEBUG_MODE == 1
		assert(actionsPerSecond > 0);
#endif
	}

	inline WindowEventListener(const WindowEventListener &listener) :
		actionsPerSecond(listener.actionsPerSecond) {
#if OGRE_DEBUG_MODE == 1
		assert(actionsPerSecond > 0);
#endif
	}

	inline virtual ~WindowEventListener() {

	}

	/**
	 * @brief Callback when graphics should update
	 */
	virtual void onGraphics() = 0;

	/**
	 * @brief Callback when actions should update, according to actionsPerSecond
	 */
	virtual void onAction(const int &interval) = 0;

	/**
	 * @brief Callback when a key has been pressed
	 * @param The key that has been pressed. See QtOgre::WindowEventListener::KEY
	 */
	virtual void onKeyPressed(const uchar &key) = 0;

	/**
	 * @brief Callback when a key has been released
	 * @param The key that has ben release. See QtOgre::WindowEventListener::KEY
	 */
	virtual void onKeyReleased(const uchar &key) = 0;

	/**
	 * @brief Callback when mouse has been moved
	 * @param x X-coordinates moved relative to the center of the screen
	 * @param y Y-coordinates moved relative to the center of the screen
	 */
	virtual void onMouseMoved(const sint &x, const sint &y) = 0;

	/**
	 * @brief Callback when the setup has been completed
	 * @param A reference to the render window that has been created
	 */
	virtual void onSetup(Ogre::RenderWindow* renderSystem) = 0;

	/**
	 * @brief Amount of actions per second
	 * @return Actions per scond as set in the constructor
	 */
	inline usint getActionsPerSecond() const {
		return actionsPerSecond;
	}

private:
	/**
	 * @brief  Amount of milliseconds to wait between each action
	 */
	const usint actionsPerSecond;
};

}

#endif // EVENTLISTENER_H
